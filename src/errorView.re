module ErrorView = {
  include ReactRe.Component;
  type props = unit;
  let name = "ErrorView";
  let render _ => {
    <div className="ErrorView">
      (ReactRe.stringToElement "Error!!!")
    </div>;
  };
};

include ReactRe.CreateComponent ErrorView;

let createElement = wrapProps ();
