








function initControl(){

  

  document.body.addEventListener('click', function(evt){
    if (evt.target.className === "mote_w"){
      // get ip
      let ip = evt.target.getAttribute("data-ip");
      let mot = findMote(ip);

      fetch("http://"+ip+"/log")
      .then(res => res.json())
      .then(data => {
        mot.$wrapper.append(" Live!!!");

        // log("hurr");

        mot.poll = setInterval(()=>{
        console.log("?");
          // log("?");
        }, 1000);

        console.log(data);
        let log = $id("control_monitor");
        log.append(data.recent);
        log.innerHTML += "<BR>";



      
      })
      .catch(er => {
        // log(er);
      });


    }
  }, false);




};




function scanMotes(){

  // clear list
  liveMotes.forEach((tm)=>{clearInterval(tm.poll)});
  liveMotes = [];
  document.querySelector("#available_mobs").innerHTML="...";


  let sweepTill = 14;
  for (var i = 1; i < sweepTill; i++){
    let ip = '192.168.2.'+i;
    let tar = 'http://'+ip+'/marco';
    
    fetch(tar)
    .then(respo => respo.text())
    .then(data => {
      // console.log(data);
      let tIp = ip;
      let mot = findMote(tIp);
      log("got "+tIp)
      if (!mot){

        mot = new Mote({name:data, ip:tIp});
        liveMotes.push(mot);
        mot.init();
      }
      // if (mot)
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

  this.poll;
}
Mote.prototype.init = function(){
  this.$wrapper = newDiv({className:"mote_w", content:this.name});
  this.$wrapper.setAttribute("data-ip",this.ip); 
  var img = document.createElement("img");
  img.src = "/favicon/favicon-32x32.png";
  this.$wrapper.append(img);
  this.$wrapper.append(this.ip);
  document.querySelector("#available_mobs").append(this.$wrapper);


}


function findMote(ip){
  for(var i=0; i<liveMotes.length; i++){
    if (ip == liveMotes[i].ip) return liveMotes[i];
  }
  return false;
}

