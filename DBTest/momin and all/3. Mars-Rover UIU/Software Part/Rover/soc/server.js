

const express = require('express');
//const appModel = require("./models/appModel");
const app = express();
//const upload = require('express-fileupload');
//md5 = require('md5');

app.use(express.static("./static"));
app.set('view engine', 'ejs');

//setting up session
//const session = require("express-session");
//const { query } = require('./helper/db');

//app.use(session({ secret: 'ssshhhhh', saveUninitialized: true, resave: true }));

//setting up bodyparser
app.use(express.urlencoded({ extended: false }));
app.use(express.json());
//app.use(upload());
app.listen(3000);

app.get('/',(req,res)=>
{
  console.log("GETTING");
})

app.post('/',(req,res)=>
{
  console.log("POSTING");
})

app.get('/get_x',(req,res)=>
{
  res.render('test.ejs');
})

app.post('/test',(req, res) => {
  console.log(JSON.parse(JSON.stringify(req.body)));
  res.redirect('/get_x');
});

app.get('/test_x',(req,res)=>
{
  let val = req.query.sid;
  console.log("Got from client: "+val);
  res.send("5");
})


/*const express = require('express');
const app = express();
const http = require('http');
const server = http.createServer(app);
const  Server  = require("socket.io");
const io = Server(server);

app.get('/', (req, res) => {
  res.sendFile(__dirname + '/demo.html');
});

io.on('connection', (socket) => {
  console.log('a user connected');
  socket.on('disconnect', () => {
    console.log('user disconnected');
  });
});



server.listen(3000, () => {
  console.log('listening on *:3000');
});*/