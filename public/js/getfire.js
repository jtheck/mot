





////////////////////////////////
// GetFire.net chat API v1
////////////////////////////////



(function(win){
  var CHAT = win.CHAT = function(config) {

    var name = config.topic || "Fire";
    var fullHeight = config.fullHeight || false;
    var startOpen = config.startOpen || true;


    var width;
    var height;

    // var uri = "https://getfire.net/api/v1";
    var uri = "http://localhost:3000/api/v1";




    CHAT.ready = false;

    CHAT.id;

    CHAT.uuid;
    CHAT.user = makeID();
    CHAT.name = "Anonymous";
    CHAT.color = makeColor();
    // CHAT.img;


    CHAT.preview = [];

    win.addEventListener("resize", resize);
    win.addEventListener("click", hClick);



    // wrapper
    var $wrapper = newDiv({id:"getfire_wrapper"});
    document.body.append($wrapper);

    // topic
    CHAT.$topic = newDiv({id:"getfire_topic"});
    $wrapper.append(CHAT.$topic);

    // icon
    var iconSVG = '<svg xmlns:svg="http://www.w3.org/2000/svg" xmlns="http://www.w3.org/2000/svg" height="100%" width="100%" version="1.1" viewBox="0 0 60 60"><g transform="translate(0 -992.36)"><g transform="matrix(.32337 0 0 .32337 -186.23 919.22)"><g class="ftb_fill" transform="matrix(1.2471055,0,0,1.2471055,-127.95546,-112.95681)" style="stroke-width:7.3;stroke:none;"><ellipse rx="8.7" ry="8.1" cy="352.8" cx="609.4"></ellipse><ellipse rx="10.2" ry="9.5" cy="351.4" cx="632.2"></ellipse></g><path d="m598 261.9c-10.9 6.6-22.6 71.8-1.8 94.5 16.4 17.9 116.6-11.1 129.9 34.7 12.6-29.8-1.1-16.3 15.9-33.7 21.5-22.1 9.9-89.6-0.8-94.8-14.6-7.6-129-7.2-143.1-0.6z" style="fill:none;stroke-width:11"></path></g></g></svg>'
    var $icon = newDiv({id:"getfire_icon", content:iconSVG, title:"Chat!"});
    $wrapper.append($icon);
    $icon.onclick = function() {
      $icon.style.display = "none";
      CHAT.$preview.style.display = "block";
    };

    // preview
    var previewSVG = '<svg xmlns:svg="http://www.w3.org/2000/svg" xmlns="http://www.w3.org/2000/svg" height="100%" width="100%" version="1.1" viewBox="0 0 90 60">    	<style>    	.s0{    		fill-opacity:0.5;    		fill:#000;    		stroke:#fff;     		stroke-width:3;    	}    	</style>          <g transform="translate(29.95447,-990.73741)">        <g transform="matrix(0.32337,0,0,0.32337,-186.23,917.75996)" class="s0">          <path d="m507.3 255c-10.9 6.6-18.8 83 2 105.7 15.7 19.4 210-15.6 210 35.7 12-18.3 1.5-18.5 16.3-32.1 21.5-22.1 15.1-101.2-1.2-109.2-11.8-10.4-209.7-12.8-226.9 0.1z"/>        </g>      </g>    </svg>';
    CHAT.$preview = newDiv({id:"gf_preview", content:previewSVG});
    $wrapper.append(CHAT.$preview);
    CHAT.$preview.onclick = function() {
      CHAT.$topic.style.display = "block";
      CHAT.$preview.style.display = "none";
    };
    // preview name
    $pName = newDiv({id:"gf_pname", content: name});
    CHAT.$preview.append($pName);
    // preview content
    $pContent = newDiv({id:"gf_pcontent", content: "<BR><BR>Awaiting comment..."});
    CHAT.$preview.append($pContent);
    // expore (close)
    $explore = newDiv({id:"gf_exp", content: "○"});
    CHAT.$preview.append($explore);
    $explore.onclick = function(e) {
      CHAT.$preview.style.display = "none";
      $icon.style.display = "block";
      e.stopPropagation();
    };

    // head
    var $head = newDiv({id:"gf_topic_head", content:name});
    CHAT.$topic.append($head);
    $head.onclick = function() {
      CHAT.$topic.style.display = "none";
      CHAT.$preview.style.display = "block";
    };

    // card
    var $card = newDiv({id:"gf_card"});
    CHAT.$topic.append($card);
    $card.onclick = function() {
      $settings.style.display = $settings.style.display === "block" ? "none" : "block";
    };

    // toggle size button
    var $tsb = newDiv({id:"gf_tsb", content:" ➕ "});
    CHAT.$topic.append($tsb);
    $tsb.onclick = function() {
      fullHeight = fullHeight ? false : true;
      resize();
    };

    // content
    $content = newDiv({id:"gf_topic_content"});
    CHAT.$topic.append($content);

    // messages
    CHAT.$messages = newDiv({id:"gf_messages"});
    $content.append(CHAT.$messages);
    CHAT.$messages.classList.add("gf_scroll");

    // settings
    var $settings = newDiv({id:"gf_settings"});
    $content.append($settings);

    // FORM
    var $form = document.createElement("form");
    $form.setAttribute("autocomplete", "off");
    // text area
    var $input = document.createElement("textarea");
    $input.setAttribute('placeholder', "compose your message");
    $input.id = "gf_message_entry";
    $input.classList.add("gf_scroll");
    // send button
    var $submit = document.createElement("input");
    $submit.setAttribute('type',"submit");
    $submit.setAttribute('value',"Send");
    // $submit.style.cssText = styles.gfSubmitId;//setAttribute("style", styles.gfSubmitId);
    $submit.id = "gf_submit";
    $submit.onclick = function() {
      CHAT.postMessage({
        content: $input.value,
        topic: CHAT.id,
        color: CHAT.color,
        user: CHAT.user,
        name: CHAT.name
      });
      return false; // prevent default form submission
    };
    $form.append($input);
    $form.append($submit);
    CHAT.$topic.append($form);







    // pub sub
    var pubk = "pub-c-1792f899-2843-41fa-bb31-28d7190cee7a";
  	var subk = "sub-c-8835c7da-7a67-11e4-b197-02ee2ddab7fe";
  	CHAT.pn = new PubNub({
  	 	subscribeKey: subk,
  	 	publishKey: pubk,
  	 	ssl: true
  	});
    // get user id
    if (document.cookie.indexOf("gfa_pn_uuid=") >= 0) CHAT.uuid = getCookie("gfa_pn_uuid");
    else CHAT.uuid = setCookie("gfa_pn_uuid", Math.random().toString(36).substring(2, 15) + "GF_applet" + Math.random().toString(36).substring(2, 15));
    CHAT.pn.uuid = CHAT.uuid;
    // listen
    CHAT.pn.addListener({
      status: function(s) {},
      message: function(m) {
        // console.log(m);
        renderMessage(m.message.content);
      }
    });

    subscribe();

    resize();

    if (startOpen) {
      CHAT.$topic.style.display = "block";
      CHAT.$preview.style.display = "none";
      $icon.style.display = "none";
    }

    // completed init







    function subscribe() {
      var xhr = window.XMLHttpRequest ? new XMLHttpRequest() : new ActiveXObject('Microsoft.XMLHTTP');
      var params = JSON.stringify({name: name});

      xhr.open("post", uri+"/index", true);
      xhr.setRequestHeader('Content-Type','application/json; charset=utf-8');
      xhr.onload = function(){
        // success
        if (xhr.status === 200) {
          var data = JSON.parse(xhr.responseText).data;
          if (data) {
            // prepare topic
            CHAT.id = data.hashish;
            CHAT.pn.subscribe({
              channels : ["ft-" + CHAT.id]
            });

            $settings.innerHTML += data.summary;
            $head.innerHTML = $pName.innerHTML = data.name;
//TODO: sharing links, watching count

            var messages = JSON.parse(xhr.responseText).messages;
  // console.log(messages);

            // render messages
            for (var i=0; i<messages.length; i++) {
              renderMessage(messages[i]);
            }


            CHAT.ready = true;
          } else {
            // no topic returned
            CHAT.$topic.style.display = "none";
            CHAT.$preview.style.display = "block";
            $icon.style.display = "none";
            $pContent.innerHTML = CHAT.$messages.innerHTML = "<BR><BR>Topic not found!";
            console.log("Subscribe failed!");
          }
        } else {
          // failure
          console.log('Request failed: ' + xhr.status);
        }
      };

      // console.log(params);
      xhr.send(params);
      return true;
    };


    function publish(data) {
      CHAT.pn.publish({
    		channel : "ft-" + CHAT.id,
    		message : {
    			type : "new_message",
    			content : data,
          profile : CHAT.user
    		}
    	}, function (status, response) {
          if (status.error) {
              // console.log(status);
          } else {

            // clear message entry
            $input.value = "";

            // var message = <%= raw @message %>;
            // <% if current_user %>
            // 	$("#me_<%= @topic.hashish %>").find(".message_entry_content").val("");
            // <% else %>
            // 	$(".pcw_me").val("");
            // <% end %>

            // renderMessage()
            // console.log(response);
          }
      });
    };



    CHAT.postMessage = function(msg) {
      if (!CHAT.ready) return false;

      var xhr = window.XMLHttpRequest ? new XMLHttpRequest() : new ActiveXObject('Microsoft.XMLHTTP');
      var params = JSON.stringify({content: msg.content, topic_id: msg.topic, color: msg.color, user_id: msg.user, name: msg.name, response_to:"null"});

      xhr.open("post", uri+"/message", true);
      xhr.setRequestHeader('Content-Type','application/json; charset=utf-8');
      xhr.onload = function(){
        // success
        if (xhr.status === 200) {
          var data = JSON.parse(xhr.responseText).data;
          if (data && data.content != "") {
            data = JSON.parse(data);
	           publish(data);
          }
        } else {
          // failure
          console.log('Request failed: ' + xhr.status);
        }
      };

      // console.log(params);
      xhr.send(params);

    };





    CHAT.rules = function() {
      alert("be a baws<br>dont be trash");
      return true;
    };


    function renderMessage(m) {
      if (!m) return false;

      // message
      var $tMsg = newDiv({className: "gf_msg", content: m.content});
      // name
      var $name =document.createElement("span");
      $name.classList.add("gf_mName");
      $name.innerHTML = m.name+"‧ ";
      $name.style.color = m.color;
      $tMsg.prepend($name);

      CHAT.$messages.append($tMsg);
      CHAT.$messages.scrollTo(0, CHAT.$messages.scrollHeight);


      renderPreview(m.content);


      if (CHAT.$topic.style.display == "none" && CHAT.$preview.style.display == "none") {
        CHAT.$preview.style.display = "block";
        $icon.style.display = "none";
      }

      return true;
    };



    function renderPreview(m) {

      var pCount = $pContent.getElementsByClassName("gf_pMsg").length;
      if (pCount == 0) $pContent.innerHTML = "";

  		var $newMsg = newDiv({className:"gf_pMsg", content:m});
      $pContent.append($newMsg);

      if (pCount > 4) $pContent.getElementsByClassName("gf_pMsg")[0].remove();

      return true;
    };


    // global click handler
    function hClick(e) {
      // click is inside applet
      if (e.path.includes($wrapper)) {
        // click is not in settings
        if (!e.path.includes($settings) && !e.path.includes($card)) $settings.style.display = "none";
      } else {
        // click is not inside applet
        if (!fullHeight && $icon.style.display == "none") {
          CHAT.$topic.style.display = "none";
          CHAT.$preview.style.display = "block";
        }
      }
    };


    function newDiv(div) {
      var $div = document.createElement('div');

      $div.id = div.id || "";
      $div.className = div.className || "";
      $div.setAttribute('title', (div.title || ""));
      $div.innerHTML = div.content || "";

      return $div;
    };


    function resize() {
      var width = Math.min(Math.max(win.innerWidth/3, 316), win.innerWidth);
      var height = win.innerHeight;

      CHAT.$topic.style.width = width;
      CHAT.$topic.style.height = fullHeight ? height : 316;

      return true;
    };


    function getCookie(name) {
      match = document.cookie.match(new RegExp(name + '=([^;]+)'));
      if (match) return match[1];
      else return false;
    };


    function setCookie(name, value) {
    	var cookie = name + "=" + encodeURIComponent(value);
    	cookie += "; max-age=" + (4*365*24*60*60);
    	cookie += "; path=/";

    	document.cookie = cookie;
      return true;
    };


    function makeColor() {
      var hexletters = '0123456789ABCDEF',
          color = '#';
      for (var i = 0; i < 6; i++ ) color += hexletters[Math.floor(Math.random() * 16)];
      return color;
    };


    function makeID() {
      var rando = "";
      var possible = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
      for( var i=0; i < 8; i++ )
        rando += possible.charAt(Math.floor(Math.random() * possible.length));
      return "NOID-" + rando;
    };

    return CHAT;
  };
})(window);





//  for(i = 0; i < images.length; i++) {
// var images = document.querySelectorAll(".preview-image");
//   (function(i){
//     images[i].addEventListener('click', function () {
//         // function code here
//     });
//   })(i)
// }
