


var init = function(){
  initRepo();
  initTraining();
  initControl();

  // // Init chat
  // if (typeof GETFIRE !== "undefined"){
  //   var chat = GETFIRE({topicNames: ["mot moe", 'test'],
  //     defaultName: Math.random() > .5 ? "Beep" : "Boop",
  //     startOpen: false,
  //     startPreview: false,
  //     clickAwayHide: false,
  //     mouseOutFade: true,
  //     titleAlerts: true,
  //     topCorner: false,
  //     devMode: (window.location.protocol != 'https:')});
  // }



  window.addEventListener('hashchange', handleHashChange);


  let header = $id('header');
  header.onclick = function(e){
    if (e.target.id !== "header"){
      loadPage(e.target.id.slice(2));
    }
  }


  // Check compatibility for the browser we're running this in
  if ("serviceWorker" in navigator) {
    if (navigator.serviceWorker.controller) {
      // console.log("sw active service worker found, no need to register");
    } else {
      // Register the service worker
      navigator.serviceWorker
        .register("sw-momo.js", {
          scope: "./"
        })
        .then(function (reg) {
          // console.log("sw Service worker has been registered for scope: " + reg.scope);
        });
    }
  }
  

  handleHashChange();
  
  log("©'25 Mot.moe");
}
  


function loadPage(p){
  let p_home = $id('page_home');
  let p_repo = $id('page_repository');
  let p_train = $id('page_training');
  let p_control = $id('page_control');
  let p_help = $id('page_help');

  p_home.style.display = 'none';
  p_train.style.display = 'none';
  p_repo.style.display = 'none';
  p_control.style.display = 'none';
  p_help.style.display = 'none';

  switch(p){
    case 'code':
      p_repo.style.display = 'block';
    break;
    case 'train':
      p_train.style.display = 'block';
    break;
    case 'help':
      p_help.style.display = 'block';
    break;
    case 'control':
      p_control.style.display = 'block';
    break;
    default:
    case 'home':
      p_home.style.display = 'block';
    break;
  }

  if (p == 'home')
    history.replaceState(null, "", window.location.pathname + window.location.search);
  else 
    window.location.hash = p;
}


function handleHashChange() {
  const hash = window.location.hash; // Get the current hash (e.g., "#page1")
  const page = hash.substring(1); // Remove the "#" to get the page name (e.g., "page1")
  if (page) {
    loadPage(page); // Load the corresponding page
  } else {
    loadPage('home'); // Default page if no hash is present
  }
}