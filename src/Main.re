
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

let wait = 20;

type config = {
  lineSwap: float,
  beat: float,
  main: float,
  sub: float,
  mainNum: int,
  subNum: int,
  fade: bool,
  lineWidth: float,
  traceWidth: float,
  colored: bool,
  wave: bool,
};

let defaults = {
  lineSwap: 0.,
  beat: 5000., main: 100., sub: 80., mainNum: 3, subNum: 6,
  fade: true, traceWidth: 0., colored: false,
  lineWidth: 0.,
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
  ("wavy", {...outerCousins, subNum: 3, main: 40., sub: 30., wave: true, beat: 2000., fade: true}),
  ("wavy", {...outerCousins, subNum: 3, mainNum: 6, main: 30., sub: 60., wave: true, beat: 2000., fade: true}),
  ("wavy", {...outerCousins, subNum: 2, mainNum: 4, main: 20., sub: 40., wave: true, beat: 2000., fade: true}),
  ("wavy", {...outerCousins, subNum: 4, mainNum: 4, main: 30., sub: 60., wave: true, beat: 2000., fade: true, lineWidth: 10., traceWidth: 1.}),
  ("wavy", {...outerCousins, subNum: 4, mainNum: 4, main: 60., sub: 30., wave: true, beat: 4000., fade: false}),
  ("wavy", {...outerCousins, subNum: 4, mainNum: 8, main: 90., sub: 30., wave: true, beat: 4000., fade: false}),
  ("wavy", {...outerCousins, subNum: 2, mainNum: 8, main: 90., sub: 30., wave: true, beat: 4000., fade: false}),
  ("wavy", {...outerCousins, subNum: 2, mainNum: 8, main: 80., sub: 50., wave: true, beat: 4000., fade: true, traceWidth: 20., lineSwap: 12000. }),
];

let swappa = (a) => {
  if (a < 0.5) {
    16. *. a *. a *. a *. a *. a
  } else {
    let a = a -. 1.;
    1. +. 16. *. a *. a *. a *. a *. a
  }
};

let upAndDown = (~t, ~period) => {
  let a = mod_float(t, period) /. period;
  if (a < 0.5) {
    swappa(a *. 2.)
  } else {
    swappa((1. -. a) *. 2.)
  }
};

let circles = ({beat, main, sub, mainNum, subNum, fade, lineWidth, traceWidth, colored, wave, lineSwap}, ctx, t) => {
  let colors = [|"red", "green", "blue", "orange", "purple", "black", "brown", "teal"|];

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
  let alignmentScale = (sub === 0. ? 1. : sub /. main);
  for (i in 0 to (mainNum - 1)) {
    let theta = (float_of_int(i) /. float_of_int(mainNum) +. /*(float_of_int(i)) /. 100. +. */t /. beat) *. tau;
    let cpos = rotateAround((cx, cy), main, theta);
    if (traceWidth !== 0.) {
      if (colored) {
        C.setStrokeStyle(ctx, colors[i mod Array.length(colors)]);
      };
      C.beginPath(ctx);
      if (lineSwap !== 0.) {
        let linee = upAndDown(~t, ~period=lineSwap) *. 0.3;
        /* let linee = (mod_float(t, lineSwap)) /. lineSwap -. 0.5 |> abs_float; */
        C.setGlobalAlpha(ctx, linee);
      };
      C.setStrokeWidth(ctx, traceWidth);
      C.circle(ctx, cpos, sub);
      C.stroke(ctx);
    };
    if (lineSwap !== 0.) {
      /* let linee = upAndDown(~t, ~period=lineSwap) *. 0.5; */
      /* let linee = (mod_float(t, lineSwap)) /. lineSwap -. 0.5 |> abs_float; */
      /* C.setGlobalAlpha(ctx, (0.5 -. linee +. 0.01)); */
      C.setGlobalAlpha(ctx, 0.3);
    };
    for (j in 0 to (subNum - 1)) {
      let percentAround = float_of_int(j) /. float_of_int(subNum);
      let theta = (t /. beat /. alignmentScale +. percentAround) *. tau;
      if (lineWidth !== 0.) {
        let posA = rotateAround(cpos, sub -. 15., theta);
        let posB = rotateAround(cpos, sub +. 15., theta);
        if (colored) {
          C.setStrokeStyle(ctx, colors[i mod Array.length(colors)]);
        };
        C.setStrokeWidth(ctx, lineWidth);
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
