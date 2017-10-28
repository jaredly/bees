
let module C = MyDom.Canvas;

let tau = Js.Math._PI *. 2.;

let rotateAround = ((cx, cy), r, t) => {
  (
    cx +. (cos(t) *. r),
    cy +. (sin(t) *. r),
  )
};


let glitchCircles = (ctx, t) => {
  C.setGlobalAlpha(ctx, 0.1);
  C.clearRect(ctx, 0., 0., 1000., 1000.);
  let cx = 500.;
  let cy = 500.;
  for (i in 0 to 40) {
  C.beginPath(ctx);
    let theta = (float_of_int(i) *. /*(float_of_int(i)) /. 100. +. */t /. 1000.) *. tau;
    /* Js.log(theta); */
    let pos = rotateAround((cx, cy), 50., theta);
    C.circle(ctx, pos, 10.);
  C.fill(ctx);
  };
};

let waiting = (ctx, t) => {
  C.setGlobalAlpha(ctx, 0.3);
  C.setFillStyle(ctx, "white");
  C.fillRect(ctx, 0., 0., 1000., 1000.);
  /* C.clearRect(ctx, 0., 0., 1000., 1000.); */
  C.setFillStyle(ctx, "black");
  C.setGlobalAlpha(ctx, 0.2);
  let cx = 500.;
  let cy = 500.;
  for (i in 0 to 2) {
    C.beginPath(ctx);
    let theta = (float_of_int(i) /. 3. +. /*(float_of_int(i)) /. 100. +. */t /. 1000.) *. tau;
    /* Js.log(theta); */
    let pos = rotateAround((cx, cy), 100., theta);
    C.circle(ctx, pos, 10.);
    C.fill(ctx);
  };
};

let cousins = (ctx, t) => {
  let beat = 5000.;
  C.setGlobalAlpha(ctx, 0.3);
  C.setFillStyle(ctx, "white");
  C.fillRect(ctx, 0., 0., 1000., 1000.);
  /* C.clearRect(ctx, 0., 0., 1000., 1000.); */
  C.setFillStyle(ctx, "black");
  C.setGlobalAlpha(ctx, 0.2);
  let cx = 500.;
  let cy = 500.;
  for (i in 0 to 2) {
    let theta = (float_of_int(i) /. 3. +. /*(float_of_int(i)) /. 100. +. */t /. beat) *. tau;
    let cpos = rotateAround((cx, cy), 100., theta);
    for (j in 0 to 5) {
      C.beginPath(ctx);
      let pos = rotateAround(cpos, 70., (t /. beat /. 0.7 +. float_of_int(j) /. 6.) *. tau);
      /* Js.log(theta); */
      C.circle(ctx, pos, 10.);
      C.fill(ctx);
    }
  };
};

let outerCousins = (ctx, t) => {
  let beat = 5000.;
  let main = 100.;
  let sub = 150.;
  C.setGlobalAlpha(ctx, 0.3);
  C.setFillStyle(ctx, "white");
  C.fillRect(ctx, 0., 0., 1000., 1000.);
  /* C.clearRect(ctx, 0., 0., 1000., 1000.); */
  C.setFillStyle(ctx, "black");
  C.setGlobalAlpha(ctx, 0.2);
  let cx = 500.;
  let cy = 500.;
  for (i in 0 to 2) {
    let theta = (float_of_int(i) /. 3. +. /*(float_of_int(i)) /. 100. +. */t /. beat) *. tau;
    let cpos = rotateAround((cx, cy), main, theta);
    for (j in 0 to 5) {
      C.beginPath(ctx);
      let pos = rotateAround(cpos, sub, (t /. beat /. (sub /. main) +. float_of_int(j) /. 6.) *. tau);
      /* Js.log(theta); */
      C.circle(ctx, pos, 10.);
      C.fill(ctx);
    }
  };
};

let franticCousins = (ctx, t) => {
  let beat = 2000.;
  let main = 100.;
  let sub = 150.;
  let mainNum = 3;
  let subNum = 6;
  C.setGlobalAlpha(ctx, 0.3);
  C.setFillStyle(ctx, "white");
  C.fillRect(ctx, 0., 0., 1000., 1000.);
  /* C.clearRect(ctx, 0., 0., 1000., 1000.); */
  C.setFillStyle(ctx, "black");
  C.setGlobalAlpha(ctx, 0.2);
  let cx = 500.;
  let cy = 500.;
  for (i in 0 to (mainNum - 1)) {
    let theta = (float_of_int(i) /. float_of_int(mainNum) +. /*(float_of_int(i)) /. 100. +. */t /. beat) *. tau;
    let cpos = rotateAround((cx, cy), main, theta);
    for (j in 0 to (subNum - 1)) {
      C.beginPath(ctx);
      let pos = rotateAround(cpos, sub, (t /. beat /. (sub /. main) +. float_of_int(j) /. float_of_int(subNum)) *. tau);
      /* Js.log(theta); */
      C.circle(ctx, pos, 10.);
      C.fill(ctx);
    }
  };
};

let hexCousins = (ctx, t) => {
  let beat = 2000.;
  let main = 100.;
  let sub = 150.;
  let mainNum = 6;
  let subNum = 6;
  C.setGlobalAlpha(ctx, 0.3);
  C.setFillStyle(ctx, "white");
  C.fillRect(ctx, 0., 0., 1000., 1000.);
  /* C.clearRect(ctx, 0., 0., 1000., 1000.); */
  C.setFillStyle(ctx, "black");
  C.setGlobalAlpha(ctx, 0.2);
  let cx = 500.;
  let cy = 500.;
  for (i in 0 to (mainNum - 1)) {
    let theta = (float_of_int(i) /. float_of_int(mainNum) +. /*(float_of_int(i)) /. 100. +. */t /. beat) *. tau;
    let cpos = rotateAround((cx, cy), main, theta);
    for (j in 0 to (subNum - 1)) {
      C.beginPath(ctx);
      let pos = rotateAround(cpos, sub, (t /. beat /. (sub /. main) +. float_of_int(j) /. float_of_int(subNum)) *. tau);
      /* Js.log(theta); */
      C.circle(ctx, pos, 10.);
      C.fill(ctx);
    }
  };
};

let confetti = (ctx, t) => {
  let colors = [|"red", "green", "blue", "orange", "purple", "black"|];
  let beat = 5000.;
  let main = 200.;
  let sub = 150.;
  let mainNum = 6;
  let subNum = 6;
  C.setGlobalAlpha(ctx, 1.);
  C.setFillStyle(ctx, "white");
  C.fillRect(ctx, 0., 0., 1000., 1000.);
  /* C.clearRect(ctx, 0., 0., 1000., 1000.); */
  C.setFillStyle(ctx, "black");
  C.setGlobalAlpha(ctx, 0.2);
  let cx = 500.;
  let cy = 500.;
  for (i in 0 to (mainNum - 1)) {
    let theta = (float_of_int(i) /. float_of_int(mainNum) +. /*(float_of_int(i)) /. 100. +. */t /. beat) *. tau;
    let cpos = rotateAround((cx, cy), main, theta);
    /* C.beginPath(ctx);
    C.setStrokeWidth(ctx, 1.);
    C.circle(ctx, cpos, sub);
    C.stroke(ctx); */
    for (j in 0 to (subNum - 1)) {
      let theta = (t /. beat /. (sub /. main) +. float_of_int(j) /. float_of_int(subNum)) *. tau;
      let posA = rotateAround(cpos, sub -. 15., theta);
      let posB = rotateAround(cpos, sub +. 15., theta);
      C.setStrokeStyle(ctx, colors[i]);
      C.setStrokeWidth(ctx, 10.);
      C.line(ctx, posA, posB);
      /* Js.log(theta); */
      /* C.beginPath(ctx);
      C.circle(ctx, pos, 10.);
      C.fill(ctx); */
    }
  };
};

let outerConfetti = (ctx, t) => {
  let colors = [|"red", "green", "blue", "orange", "purple", "black"|];
  let beat = 5000.;
  let main = 100.;
  let sub = 150.;
  let mainNum = 6;
  let subNum = 6;
  C.setGlobalAlpha(ctx, 1.);
  C.setFillStyle(ctx, "white");
  C.fillRect(ctx, 0., 0., 1000., 1000.);
  /* C.clearRect(ctx, 0., 0., 1000., 1000.); */
  C.setFillStyle(ctx, "black");
  C.setGlobalAlpha(ctx, 0.2);
  let cx = 500.;
  let cy = 500.;
  for (i in 0 to (mainNum - 1)) {
    let theta = (float_of_int(i) /. float_of_int(mainNum) +. /*(float_of_int(i)) /. 100. +. */t /. beat) *. tau;
    let cpos = rotateAround((cx, cy), main, theta);
    /* C.beginPath(ctx);
    C.setStrokeWidth(ctx, 1.);
    C.circle(ctx, cpos, sub);
    C.stroke(ctx); */
    for (j in 0 to (subNum - 1)) {
      let theta = (t /. beat /. (sub /. main) +. float_of_int(j) /. float_of_int(subNum)) *. tau;
      let posA = rotateAround(cpos, sub -. 15., theta);
      let posB = rotateAround(cpos, sub +. 15., theta);
      C.setStrokeStyle(ctx, colors[i]);
      C.setStrokeWidth(ctx, 10.);
      C.line(ctx, posA, posB);
      /* Js.log(theta); */
      /* C.beginPath(ctx);
      C.circle(ctx, pos, 10.);
      C.fill(ctx); */
    }
  };
};

let toss = (ctx, t) => {
  let colors = [|"red", "green", "blue", "orange", "purple", "black"|];
  let beat = 5000.;
  let main = 100.;
  let sub = -150.;
  let mainNum = 4;
  let subNum = 8;
  C.setGlobalAlpha(ctx, 0.3);
  C.setFillStyle(ctx, "white");
  C.fillRect(ctx, 0., 0., 1000., 1000.);
  /* C.clearRect(ctx, 0., 0., 1000., 1000.); */
  C.setFillStyle(ctx, "black");
  C.setGlobalAlpha(ctx, 0.2);
  let cx = 500.;
  let cy = 500.;
  for (i in 0 to (mainNum - 1)) {
    let theta = (float_of_int(i) /. float_of_int(mainNum) +. /*(float_of_int(i)) /. 100. +. */t /. beat) *. tau;
    let cpos = rotateAround((cx, cy), main, theta);
    /* C.beginPath(ctx);
    C.setStrokeWidth(ctx, 1.);
    C.circle(ctx, cpos, sub);
    C.stroke(ctx); */
    for (j in 0 to (subNum - 1)) {
      let theta = (t /. beat /. (sub /. main) +. float_of_int(j) /. float_of_int(subNum)) *. tau;
      /* let posA = rotateAround(cpos, sub -. 15., theta);
      let posB = rotateAround(cpos, sub +. 15., theta);
      C.setStrokeStyle(ctx, colors[i mod Array.length(colors)]);
      C.setStrokeWidth(ctx, 10.);
      C.line(ctx, posA, posB); */
      /* Js.log(theta); */
      let pos = rotateAround(cpos, sub, theta);
      C.setFillStyle(ctx, colors[i mod Array.length(colors)]);
      C.beginPath(ctx);
      C.circle(ctx, pos, 10.);
      C.fill(ctx);
    }
  };
};
