
let tau = Js.Math._PI *. 2.;

let rotateAround = (~pos as (cx, cy), ~around as (x, y), ~theta) => {
  let theta = atan2(y -. cy, x -. cx) +. theta;
  let dx = x -. cx;
  let dy = y -. cy;
  let radius = sqrt(dx *. dx +. dy *. dy);
  (
    cx +. cos(theta) *. radius,
    cy +. sin(theta) *. radius,
  )
};

let circleAround = (~center as (cx, cy), radius, count) => {
  let rec loop = (i) => {
    if (i === 0) {
      []
    } else {
      let percent = float_of_int(i) /. float_of_int(count);
      let theta = tau *. percent;
      [(
        cx +. cos(theta) *. radius,
        cy +. sin(theta) *. radius,
      ), ...loop(i - 1)]
    }
  };
  loop(count);
};
