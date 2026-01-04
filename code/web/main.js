import express from 'express'
const app = express();
app.use(express.static(`./`));


let port = 3000;

app.get("/", function(req, res) {
    res.sendFile("/index.html");
});
app.get("/frank", function(req, res) {
    res.sendFile("/frank/index.html");
});
app.get("/julien", function(req, res) {
    res.sendFile("/julien/index.html");
});
app.get("/photos/:photoName", function(req, res) {
    res.sendFile(`/photos/${req.params.photo}`);
});

app.listen(port);
console.log(
  `Server started at http://localhost:${port}`
);
