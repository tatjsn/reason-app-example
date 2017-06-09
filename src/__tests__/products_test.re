open Jest;
open ExpectJs;

let _ =

describe "src/products.re" (fun _ => {

  test "is defined" (fun _ => {
    let component = ReactShallowRenderer.renderWithRenderer <Products products=["Prod1"] />;
    expect (Js.Undefined.return component) |> toBeDefined;
  });

  test "renders" (fun _ => {
    let tree = Products.createElement products::["Prod1"] children::[] ()
      |> ReactShallowRenderer.renderWithRenderer;

    expect tree |> toMatchSnapshot;
  });

});
