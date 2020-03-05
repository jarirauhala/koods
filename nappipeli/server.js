const express = require('express');
const favicon = require('express-favicon');
const path = require('path');
const port = process.env.PORT || 8080;
const app = express();

var counter = 0;

console.log("server starting")

app.use(favicon(__dirname + '/build/favicon.ico'));
// the __dirname is the current directory from where the script is running
app.use(express.static(__dirname));
app.use(express.static(path.join(__dirname, 'build')));

app.get('/secretpathforcounterfetching', function (req, res) {
    counter = counter + 1;

    const counterStr = ''+counter;
    console.log("counter set up, ready to send: " + counterStr);
    return res.send(counterStr);
});

app.get('/*', function (req, res) {
  res.sendFile(path.join(__dirname, 'build', 'index.html'));
});

app.listen(port);

console.log("server listening")