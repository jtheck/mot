


require('dotenv').config();


const express = require('express');
const app = express();
const port = 4000;

app.use(express.static('public'));

app.get('/', function(req, res){
  res.redirect('index.html');
});



app.listen(port, () => {console.log('mot.moe listening on port '+ port +'!')});


app.use(function (req, res, next) {
  res.status(404).send("Sorry can't find that!")
})

app.use(function (err, req, res, next) {
  console.error(err.stack)
  res.status(500).send('Something broke!')
})
