open GraphqlJsPromise;

let order =
  Schema.(
    obj("order", ~fields=_ =>
      [
        field(
          "_id",
          nonnull(string),
          ~args=Arg.[],
          ~resolve=((), order: Types.order) =>
          order._id
        ),
        field(
          "name",
          nonnull(string),
          ~args=Arg.[],
          ~resolve=((), order: Types.order) =>
          order.name
        ),
      ]
    )
  );

let rootQuery =
  Schema.(
    query([
      async_field(
        "orders",
        nonnull(list(nonnull(order))),
        ~args=Arg.[],
        ~resolve=((), _) =>
        Mongo.findAll()
        |> Js.Promise.then_((orders: array(Types.order)) =>
             Js.Promise.resolve(Ok(orders |> Array.to_list))
           )
      ),
      // async_field(
      //   "starship",
      //   starship,
      //   ~args=Arg.[arg("id", nonnull(int))],
      //   ~resolve=((), (), id) =>
      //   Swapi.getStarship(id)
      // ),
    ])
  );

let schema = Schema.create(rootQuery);
