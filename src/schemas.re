open GraphqlJsPromise;

let rootQuery =
  Schema.(
    query([
      // async_field(
      //   "order",
      //   Order.schema,
      //   ~args=Arg.[arg("_id", nonnull(string))],
      //   ~resolve=((), (), _id) =>
      //   Order.findOne(_id)
      //   |> Js.Promise.then_((orders: array(Order.t)) =>
      //        Js.Promise.resolve(Ok(orders |> Array.to_list))
      //      )
      // ),
      async_field(
        "orders",
        nonnull(list(nonnull(Order.schema))),
        ~args=Arg.[],
        ~resolve=((), _) => []

      ),
    ])
  );

let schema = Schema.create(rootQuery) /*    */;

// Order.find()
// |> Js.Promise.then_((orders: array(Order.t)) =>
//      Js.Promise.resolve(Ok(orders |> Array.to_list))
