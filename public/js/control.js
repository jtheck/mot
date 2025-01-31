








function initControl(){

 

document.body.addEventListener('click', function(evt){
  if (evt.target.className === "mote_w"){
    // get ip
    let ip = evt.target.getAttribute("data-ip");
    let mot = findMote(ip);
    fetch("http://"+ip+"/log")
    .then(respo => respo.text())
    .then(data => {
      // console.log(data);
      let log = $id("control_monitor");
      log.append(data);
      log.innerHTML += "<BR>";
    })
    .catch(er => {
      // console.log('no polo');
    });


  }
}, false);




};




function scanMotes(){

  document.querySelector("#available_mobs").innerHTML="...";


  let sweepTill = 6 ;
  for (var i = 1; i < sweepTill; i++){
    var ip = '192.168.2.'+i;
    var tar = 'http://'+ip+'/marco';
    
    fetch(tar)
    .then(respo => respo.text())
    .then(data => {
      console.log(data);
      let tIp = ip;
      let mot = findMote(tIp);
      if (!mot){

        mot = new Mote({name:data, ip:tIp});
        liveMotes.push(mot);
      }
      if (mot)
        mot.init();
    })
    .catch(er => {
      // console.log('no polo');
    });

  }

};


let liveMotes = [];

function Mote(ops){

  this.name = ops.name;
  this.ip = ops.ip;
  
  this.$wrapper;
}
Mote.prototype.init = function(){
  this.$wrapper = newDiv({className:"mote_w", content:this.name});
  this.$wrapper.setAttribute("data-ip",this.ip); 
  var img = document.createElement("img");
  img.src = "/favicon/favicon-32x32.png";
  this.$wrapper.append(img);
  document.querySelector("#available_mobs").append(this.$wrapper);


}


function findMote(ip){
  for(var i=0; i<liveMotes.length; i++){
    if (ip == liveMotes[i].ip) return liveMotes[i];
  }
  return false;
}

