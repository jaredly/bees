
let x = 10;

let module C = MyDom.Canvas;

let current = ref(None);

let animate = (ctx, fn, wait) => {
  switch current^ {
  | Some(fn) => fn()
  | None => ()
  };
  let start = Js.Date.now();
  let interval = Js.Global.setInterval(() => fn(ctx, Js.Date.now() -. start), wait);
  current := Some(() => Js.Global.clearInterval(interval));
};

let tau = Js.Math._PI *. 2.;

let rotateAround = ((cx, cy), r, t) => {
  (
    cx +. (cos(t) *. r),
    cy +. (sin(t) *. r),
  )
};

let wait = 40;

type config = {
  beat: float,
  main: float,
  sub: float,
  mainNum: int,
  subNum: int,
  fade: bool,
  lines: bool,
  trace: bool,
  colored: bool,
  wave: bool,
};

let defaults = {
  beat: 5000., main: 100., sub: 80., mainNum: 3, subNum: 6,
  fade: true, lines: false, trace: false, colored: false,
  wave: false,
};

let outerCousins = {...defaults, beat: 3000., subNum: 6, mainNum: 3, sub: 150., colored: true};

let configs = [
  ("Default", defaults),
  ("waiting", {...defaults, subNum: 1, beat: 3000., mainNum: 3, sub: 0.}),
  ("cousins", {...defaults, subNum: 6, mainNum: 3, sub: 70.}),
  ("outerCousins", outerCousins),
  ("speedyOuterCousins", {...outerCousins, beat: 1000.}),
  ("wavy", {...outerCousins, sub: 50., wave: true, beat: 7000.}),
];

let circles = ({beat, main, sub, mainNum, subNum, fade, lines, trace, colored, wave}, ctx, t) => {
  let colors = [|"red", "green", "blue", "orange", "purple", "black"|];

  if (fade) {
    C.setGlobalAlpha(ctx, 0.3);
    C.setFillStyle(ctx, "white");
    C.fillRect(ctx, 0., 0., 1000., 1000.);
  } else {
    C.clearRect(ctx, 0., 0., 1000., 1000.);
  };

  C.setFillStyle(ctx, "black");
  C.setGlobalAlpha(ctx, 0.2);
  let cx = 500.;
  let cy = 500.;
  for (i in 0 to (mainNum - 1)) {
    let theta = (float_of_int(i) /. float_of_int(mainNum) +. /*(float_of_int(i)) /. 100. +. */t /. beat) *. tau;
    let cpos = rotateAround((cx, cy), main, theta);
    if (trace) {
      C.beginPath(ctx);
      C.setStrokeWidth(ctx, 1.);
      C.circle(ctx, cpos, sub);
      C.stroke(ctx);
    };
    for (j in 0 to (subNum - 1)) {
      let theta = (t /. beat /. (sub === 0. ? 1. : sub /. main) +. float_of_int(j) /. float_of_int(subNum)) *. tau;
      if (lines) {
        let posA = rotateAround(cpos, sub -. 15., theta);
        let posB = rotateAround(cpos, sub +. 15., theta);
        if (colored) {
          C.setStrokeStyle(ctx, colors[i mod Array.length(colors)]);
        };
        C.setStrokeWidth(ctx, 10.);
        C.line(ctx, posA, posB);
      } else {
        let pos = rotateAround(cpos, sub, theta);
        if (colored) {
          C.setFillStyle(ctx, colors[i mod Array.length(colors)]);
        };
        C.beginPath(ctx);
        C.circle(ctx, pos, 10.);
        C.fill(ctx);
      };
    }
  };
};

let run = () => {
  let canvas = MyDom.createCanvas(1000., 1000.);
  let ctx = MyDom.getContext(canvas);
  MyDom.addCanvasToBody(MyDom.document, canvas);
  let (name, config) = List.nth(configs, List.length(configs) - 1);
  Js.log(name);
  animate(ctx, circles(config), wait);


  /* MyDom.Canvas.fillRect(ctx, 0., 0., 100., 100.); */
  /* C.beginPath(ctx);
  C.setGlobalAlpha(ctx, 0.1);
  C.circle(ctx, 100., 200., 50.);
  C.fill(ctx);
  Js.log("HI");
  Js.log("awesome"); */
};

run();
