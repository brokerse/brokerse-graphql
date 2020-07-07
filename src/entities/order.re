open GraphqlJsPromise;
open Mongo;

type t = {
  _id: string,
  name: string,
};

let schema =
  Schema.(
    obj("order", ~fields=_ =>
      [
        field("_id", nonnull(string), ~args=Arg.[], ~resolve=((), order: t) =>
          order._id
        ),
        field("name", nonnull(string), ~args=Arg.[], ~resolve=((), order: t) =>
          order.name
        ),
      ]
    )
  );

let mongoUrl = "mongodb://localhost:27017";

let find = () =>
  MongoDb.connectAsync(MongoDb.client, mongoUrl)
  |> Js.Promise.then_(c => {
       let db = Client.db(c, "brokerse");
       let collection = Db.collection(db, "orders");
       let d = Js.Dict.empty();
       let cursor = Collection.find(collection, d);

       Js.Promise.make((~resolve, ~reject as _) => {
         Cursor.toArray(cursor, (_, docs) => resolve(. docs))
       });
     });

let findById = (~_id: string) =>
  MongoDb.connectAsync(MongoDb.client, mongoUrl)
  |> Js.Promise.then_(c => {
       let db = Client.db(c, "brokerse");
       let collection = Db.collection(db, "orders");
       let d = Js.Dict.empty();
       //  Js.Dict.set(d, "_id", _id);
       let cursor = Collection.findOne(collection, d);

       Js.Promise.make((~resolve, ~reject as _) => {
         Cursor.toArray(cursor, (_, docs) => resolve(. docs[0]))
       });
     });
