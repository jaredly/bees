type imageElement;

type canvasRenderingContext2D;

type ctx = canvasRenderingContext2D;

type canvasElement;

type document;

type element;

type window;

type event_like('a);

type keyboardEvent;

type blob;

type url;

[@bs.val] external url : url = "URL";

[@bs.send] external createObjectURL : (url, blob) => string = "";

[@bs.send] external toBlob : (canvasElement, blob => unit) => unit = "";

let createObjectURL = createObjectURL(url);

[@bs.val] external document : document = "";

type imagedata;

[@bs.get] external data : imagedata => array(int) = "";

let make: int => imagedata = [%bs.raw
  {|
  function (size) {
    var arr = new Uint8ClampedArray(size * size * 4);
    var data = new ImageData(arr, size, size);
    return data;
  }
|}
];

[@bs.val] external window : window = "";

[@bs.get] external getBody : document => element = "body";

[@bs.send] external appendCanvas : (element, canvasElement) => unit = "appendChild";

[@bs.send] external createCanvasElement : (document, [@bs.as "canvas"] _) => canvasElement =
  "createElement";

[@bs.send] external getContext : (canvasElement, [@bs.as "2d"] _) => canvasRenderingContext2D =
  "getContext";

[@bs.send] external createImg : (document, [@bs.as "img"] _) => imageElement = "createElement";

let addCanvasToBody = (doc, canvas) => appendCanvas(getBody(doc), canvas);

[@bs.val] external setTimeout : (unit => unit, int) => int = "";

[@bs.val] external clearTimeout : int => unit = "";

[@bs.val] external requestAnimationFrame : (float => unit) => int = "";

[@bs.val] external cancelAnimationFrame : int => unit = "";

[@bs.return null_to_opt] [@bs.send]
external getElementById : (document, string) => option(element) =
  "";

[@bs.send]
external addEventListener : (document, string, event_like('a) => Js.boolean, Js.boolean) => unit =
  "";

[@bs.send]
external addEventListenerImg :
  (imageElement, string, event_like('a) => Js.boolean, Js.boolean) => unit =
  "addEventListener"; /* unsafe casts */

type imageBitmap;

[@bs.val] external createImageBitmap : canvasElement => Js.Promise.t(imageBitmap) = "";

let getOffset: canvasElement => (int, int) = [%bs.raw
  {|
  function (canvas) {
    const box = canvas.getBoundingClientRect()
    return [box.left, box.top];
  }
|}
];

/* canvas api methods */
module Canvas = {
  [@bs.set] external setFillStyle : (ctx, string) => unit = "fillStyle";
  [@bs.set] external setStrokeStyle : (ctx, string) => unit = "strokeStyle";
  [@bs.set] external setStrokeWidth : (ctx, float) => unit = "lineWidth";
  [@bs.set] external setGlobalAlpha : (ctx, float) => unit = "globalAlpha";
  [@bs.send] external fillRect : (ctx, float, float, float, float) => unit = "";
  [@bs.send] external strokeRect : (ctx, float, float, float, float) => unit = "";
  [@bs.send] external clearRect : (ctx, float, float, float, float) => unit = "";
  [@bs.send] external ellipse : (ctx, float, float, float, float, float, float, float) => unit =
    "";
  [@bs.send] external moveTo : (ctx, float, float) => unit = "";
  [@bs.get] external canvas : ctx => canvasElement = "";
  [@bs.send] external scale : (ctx, float, float) => unit = "";
  [@bs.send] external translate : (ctx, float, float) => unit = "";
  [@bs.send] external putImageData : (ctx, imagedata, float, float) => unit = "";
  [@bs.send] external drawImage : (ctx, imageBitmap, float, float, float, float) => unit = "";
  [@bs.send] external lineTo : (ctx, float, float) => unit = "";
  [@bs.send] external fill : ctx => unit = "";
  [@bs.send] external beginPath : ctx => unit = "";
  [@bs.send] external stroke : ctx => unit = "";
  let circle = (ctx, (x, y), r) => {
    ellipse(ctx, x, y, r, r, 0., 0., Js.Math._PI *. 2.);
  };
  let line = (ctx, (x, y), (a, b)) => {
    beginPath(ctx);
    moveTo(ctx, x, y);
    lineTo(ctx, a, b);
    stroke(ctx)
  };
  let polyline = (ctx, pts) => {
    beginPath(ctx);
    switch pts {
    | [(a, b), ...rest] =>
      moveTo(ctx, a, b);
      List.iter(((a, b)) => lineTo(ctx, a, b), rest);
      stroke(ctx)
    | _ => assert false
    }
  };
};

/* unsafe casts */
external imageElementToJsObj : imageElement => Js.t({..}) = "%identity";

external canvasRenderingContext2DToJsObj : canvasRenderingContext2D => Js.t({..}) = "%identity";

external canvasElementToJsObj : canvasElement => Js.t({..}) = "%identity";

external domElToCanvas : Dom.element => canvasElement = "%identity";

external keyboardEventToJsObj : keyboardEvent => Js.t({..}) = "%identity";

external elementToCanvasElement : element => canvasElement = "%identity";

external windowToJsObj : window => Js.t({..}) = "%identity";

let createBodyDiv: unit => element = [%bs.raw
  {|
  function() {
    const div = document.createElement('div')
    document.body.appendChild(div)
    return div
  }
|}
];

let createCanvas = (width: float, height: float) => {
  let elem = createCanvasElement(document);
  let jscanv = canvasElementToJsObj(elem);
  jscanv##width#=width;
  jscanv##height#=height;
  elem
};

let createCtx = (container, width, height) => {
  let canv = createCanvas(width, height);
  appendCanvas(container, canv);
  getContext(canv)
};
