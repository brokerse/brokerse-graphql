open GraphqlFuture;

let order =
  Schema.(
    obj("order", ~fields=_ =>
      [
        field(
          "name",
          nonnull(string),
          ~args=Arg.[],
          ~resolve=((), order: Types.order) => order._id
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
        ~resolve=[],
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
