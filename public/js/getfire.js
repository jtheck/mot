







////////////////////////////////
// GetFire.net Chat API
////////////////////////////////



(function(win){
  var CHAT = win.CHAT = function(config) {

    var name = config.topic || "Welcome";
    var heightDefault = config.height || "full";
    // var width = config.width || "";

    CHAT.id;

    var width;
    var height;



    win.addEventListener("resize", resize);


    // wrapper
    var $wrapper = newDiv({id:"getfire_wrapper"});
    document.body.appendChild($wrapper);

    // icon
    var iconSVG = '<svg xmlns:svg="http://www.w3.org/2000/svg" xmlns="http://www.w3.org/2000/svg" height="100%" width="100%" version="1.1" viewBox="0 0 60 60"><g transform="translate(0 -992.36)"><g transform="matrix(.32337 0 0 .32337 -186.23 919.22)"><g class="ftb_fill" transform="matrix(1.2471055,0,0,1.2471055,-127.95546,-112.95681)" style="stroke-width:7.3;stroke:none;"><ellipse rx="8.7" ry="8.1" cy="352.8" cx="609.4"></ellipse><ellipse rx="10.2" ry="9.5" cy="351.4" cx="632.2"></ellipse></g><path d="m598 261.9c-10.9 6.6-22.6 71.8-1.8 94.5 16.4 17.9 116.6-11.1 129.9 34.7 12.6-29.8-1.1-16.3 15.9-33.7 21.5-22.1 9.9-89.6-0.8-94.8-14.6-7.6-129-7.2-143.1-0.6z" style="fill:none;stroke-width:11"></path></g></g></svg>'
    var $icon = newDiv({id:"getfire_icon", content:iconSVG, title:"Chat!"});

    // topic
    CHAT.$topic = newDiv({id:"getfire_topic"});

    $wrapper.appendChild(CHAT.$topic);

    $wrapper.appendChild($icon);


    // head
    $head = newDiv({id:"gf_topic_head", content:name});
    CHAT.$topic.appendChild($head);

    // card
    $card = newDiv({id:"gf_card"});
    CHAT.$topic.appendChild($card);

    // toggle size button
    $tsb = newDiv({id:"gf_tsb", content:" ➕ "});
    CHAT.$topic.appendChild($tsb);

    // content
    $content = newDiv({id:"gf_topic_content"});
    CHAT.$topic.appendChild($content);

    // settings





    // pub sub
    var pubpk = "pub-c-1792f899-2843-41fa-bb31-28d7190cee7a";
  	var pubsk = "sub-c-8835c7da-7a67-11e4-b197-02ee2ddab7fe";
  	CHAT.pn = new PubNub({
  	 	subscribeKey: pubsk,
  	 	publishKey: pubpk,
  	 	ssl: true
  	});

    // fire.initPubSub = function() {
      // set custom uuid for user
      // if (fire.userID) {
        var uuid;
        if (document.cookie.indexOf("gfa_pn_uuid=") >= 0) {
          uuid = getCookie("gfa_pn_uuid");
        } else {
          uuid = setCookie("gfa_pn_uuid", Math.random().toString(36).substring(2, 15) + "GetFire_API" + Math.random().toString(36).substring(2, 15));
        }
        CHAT.pn.uuid = uuid;
      // }


      CHAT.pn.addListener({
        status: function(s) {
            // console.log(s);
        },
        message: function(m) {
          // console.log(m.message);

          $content.innerHTML += m.message.content.content + "<br>";

          // var type = m.channel.slice(0,2);
          // var id = m.channel.slice(3);
          // // dispatch the message based on type
          // switch (type) {
          //   case "fc":
          //     fireContact.recieveMessage(id, m.message);
          //   break;
          //   case "ft":
          //     fireTopic.recieveMessage(id, m.message);
          //   break;
          //   case "fu":
          //     fireUser.recieveMessage(m.message);
          //   break;
          //   case "fa":
          //     fireTopic.recieveTempMessage(id, m.message);
            // break;
          // }
        }
      });

    // };



    resize();

    // GetFire
    var fire = document.querySelector("#getfire_icon");
    fire.onclick  = function(e){
      // alert("get");

        mot.chat.connect();

    };









    function newDiv(div) {
      var $div = document.createElement('div');

      $div.id = div.id || "";
      $div.className = div.className || "";
      $div.setAttribute('title', (div.title || ""));
      $div.innerHTML = div.content || "";

      return $div;
    };





    function request() {

      var xhr = window.XMLHttpRequest ? new XMLHttpRequest() : new ActiveXObject('Microsoft.XMLHTTP');
      // var params = "topic=Mot_Moe";
      var params = JSON.stringify({name:"test"});

      // xhr.open("post", "http://localhost:3000/api/v1/index", true);
      xhr.open("post", "https://getfire.net/api/v1/index", true);
      xhr.setRequestHeader('Content-Type','application/json; charset=utf-8');
      xhr.onload = function(){
          //do something
          if (xhr.status === 200) {
              // alert('User\'s name is ' + xhr.responseText);
        // console.log(xhr.responseText);
        var data = JSON.parse(xhr.responseText).data;
// console.log(data.hashish);

CHAT.id = data.hashish;


        CHAT.pn.subscribe({
          channels : ["ft-" + CHAT.id]
        });

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



  function resize() {
    var width = Math.max(win.innerWidth/3, 320);
    var height = win.innerHeight;

    CHAT.$topic.style.width = width;
    CHAT.$topic.style.height = height;

    console.log()

  }





  function getCookie(name) {
    match = document.cookie.match(new RegExp(name + '=([^;]+)'));
    if (match) return match[1];
  }


  function setCookie(name, value) {
  	var cookie = name + "=" + encodeURIComponent(value);
  	cookie += "; max-age=" + (4*365*24*60*60);
  	cookie += "; path=/";
  	//cookie += "; domain=.getfire.net";

  	document.cookie = cookie;
  }


})(window);



//  for(i = 0; i < images.length; i++) {
// var images = document.querySelectorAll(".preview-image");
//   (function(i){
//     images[i].addEventListener('click', function () {
//         // function code here
//     });
//   })(i)
// }
