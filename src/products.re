module Products = {
  include ReactRe.Component;
  type props = {products: list string};
  let name = "Products";
  let render {props} => {
    let {products} = props;
    let views = products |> List.map(
      fun prod => <div key=prod>(ReactRe.stringToElement prod)</div>
    );
    <div className="Products">
      (ReactRe.stringToElement "Our products:")
      (ReactRe.arrayToElement (Array.of_list views))
    </div>;
  };
};

include ReactRe.CreateComponent Products;

let createElement ::products => wrapProps {products: products};
