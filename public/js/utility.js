
function newDiv(div){
  var $div = document.createElement('div');

  if (div.id) $div.id = div.id;
  if (div.className) $div.className = div.className;
  if (div.title) $div.setAttribute('title', div.title);
  if (div.content) $div.innerHTML = div.content;

  return $div;
};



function assert(condition, message) {
  if (!condition) {
      throw new Error(message || "Assertion failed");
  }
}

const log = console.log;