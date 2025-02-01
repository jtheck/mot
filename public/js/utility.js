
function newDiv(div){
  var $div = document.createElement('div');

  if (div.id) $div.id = div.id;
  if (div.className) $div.className = div.className;
  if (div.title) $div.setAttribute('title', div.title);
  if (div.content) $div.innerHTML = div.content;

  return $div;
};




const log = console.log;