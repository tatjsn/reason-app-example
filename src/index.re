external spaceUrl : string = "process.env.SPACE_URL" [@@bs.val];
external accessToken : string = "process.env.ACCESS_TOKEN" [@@bs.val];

Js.Promise.(
  Bs_fetch.fetch (spaceUrl ^ "/entries?access_token=" ^ accessToken ^ "&content_type=product&include=0")
  |> then_ Bs_fetch.Response.json
  |> then_ (fun json => json
            |> Js.Json.decodeObject
            |> Option.flatMap (fun dic => Js.Dict.get dic "items")
            |> Option.flatMap Js.Json.decodeArray
            |> Option.map (fun items => items
                           |> Array.to_list
                           |> List.map (fun item => item
                                         |> Js.Json.decodeObject
                                         |> Option.flatMap (fun dic => Js.Dict.get dic "fields")
                                         |> Option.flatMap Js.Json.decodeObject
                                         |> Option.flatMap (fun dic => Js.Dict.get dic "name")
                                         |> Option.flatMap Js.Json.decodeString)
                           |> List.filter Option.isSome
                           |> List.map Option.get)
            |> Option.get
            |> (fun products =>
                ReactDOMRe.renderToElementWithId <Products products=products /> "root")
            |> resolve)
  |> catch (fun _ => ReactDOMRe.renderToElementWithId <ErrorView /> "root" |> resolve)
);
