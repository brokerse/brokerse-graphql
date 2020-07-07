// open GraphqlJsPromise;

// let orders =
//   Schema.(
//     query([
//       async_field(
//         "orders",
//         nonnull(list(nonnull(Order.schema))),
//         ~args=Arg.[],
//         ~resolve=((), _) =>
//         Order.findAll()
//       ),
//     ])
//   );
