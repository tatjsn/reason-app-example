/* https://github.com/ygrek/ocaml-extlib */
module Option = {
  exception No_value;

  let get = fun
    | Some v => v
    | None => raise No_value;

  let default v => fun
    | Some v => v
    | None => v;

  let map f => fun
    | Some v => Some (f v)
    | None => None;

  let flatMap f => fun
    | Some v => f v
    | None => None;
};

Js.Promise.(
  Bs_fetch.fetch ""
  |> then_ Bs_fetch.Response.json
  |> then_ (fun json => json
            |> Js.Json.decodeObject
            |> Option.flatMap (fun dic => Js.Dict.get dic "items")
            |> Option.flatMap Js.Json.decodeArray
            |> Option.map (fun items => items |> Array.map(
                (fun item => item
                 |> Js.Json.decodeObject
                 |> Option.flatMap (fun dic => Js.Dict.get dic "fields")
                 |> Option.flatMap Js.Json.decodeObject
                 |> Option.flatMap (fun dic => Js.Dict.get dic "name")
                 |> Option.flatMap Js.Json.decodeString
                 |> Option.get
                )))
            |> Option.get
            |> Array.to_list
            |> (fun products =>
                ReactDOMRe.renderToElementWithId <Products products=products /> "root"
              )
            |> resolve)
);

/*
            |> Option.flatMap (fun dic => Js.Dict.get dic "sys")
            |> Option.flatMap Js.Json.decodeObject
            |> Option.flatMap (fun dic => Js.Dict.get dic "type")
            |> Option.flatMap Js.Json.decodeString
*/
