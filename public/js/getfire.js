







////////////////////////////////
// GetFire.net Chat API
////////////////////////////////



(function(win){
  var CHAT = win.CHAT = function(config) {

    var topic = config.topic;


    function request() {

      var xhr = window.XMLHttpRequest ? new XMLHttpRequest() : new ActiveXObject('Microsoft.XMLHTTP');

      // var params = "topic=Mot_Moe";
      var params = JSON.stringify({name:"fire dev"});

      // xhr.open("get", "http://localhost:3000/api/v1/index"+"?"+"name=Welcome", true);
// xhr.open("post", "http://localhost:3000/api/v1/index", true);
xhr.open("post", "https://getfire.net/api/v1/index", true);
      // xhr.setRequestHeader("Content-Type", "Access-Control-Allow-Origin");
      xhr.setRequestHeader('Content-Type','application/json; charset=utf-8');

      xhr.onload = function(){
          //do something
          if (xhr.status === 200) {
              // alert('User\'s name is ' + xhr.responseText);
console.log(xhr.responseText);
          }
          else {
              console.log('Request failed: ' + xhr.status);
          }
      };

      console.log(params);

      xhr.send(params);




    }


    CHAT.connect = function() {

      request();

      // alert("merp "+topic);

    }





    CHAT.rules = function() {
      alert("be a baws");
    };

    return CHAT;
  };
})(window);
