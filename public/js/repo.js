



function Project(){
  this.name = '';
  this.location = '';

  this.boards = [];
  this.features = [];
  this.availableFeatures = [];

  this.activeBoard = '';
  this.activeFeatures = [];

  this.codeRaw = '';
  this.codeLines = [];
  this.codeCurated = '';
}
let activeProject = new Project();



let directory = [
{
    group:'Miscellaneous',
    projects:[
        'Hello_World',
        'Hourglass',
        'Control'
    ]
  },
  {
    group:'Mot.Moe',
    projects:[
        'Tamago',
        'Battle Brobot'
    ]
  }
];
  







  
function selectProject(){
  let $projectSelect = $id("project_select");
  let name = $projectSelect.value;
  let $project = $id("proj_"+name.replace(' ', '_'));
  
  let project = name.replace(' ', '_');
  let group = $project.parentElement.label; 
  let folder = 'repo/'+group+'/'+project+'/';

  let path = folder+project+'.ino';

  let $logoCell = $id("project_logo");
  let $projectLogo = document.createElement("img");
  $projectLogo.src = folder+"logo.png";
  $logoCell.innerHTML = "";
  $logoCell.append($projectLogo);
  
  
  activeProject = new Project();
  activeProject.name = name;
  activeProject.location = folder;

  codeFetch(path);
}

function selectBoard(){
  let $boardSelect = $id("board_select");
  let board = $boardSelect.value;

  activeProject.activeBoard = board;
  activeProject.activeFeatures = [];

  let $boardCell = $id("project_board");
  let $boardLink = document.createElement("a");
  $boardLink.href = "images/boards/"+activeProject.activeBoard+".jpg"; 
  $boardLink.target = '_blank';
  let $projectBoard = document.createElement("img");
  $projectBoard.src = "images/boards/"+activeProject.activeBoard+".jpg";
  $boardCell.innerHTML = "";
  $boardLink.append($projectBoard);
  $boardCell.append($boardLink);

  $featureSelect = $id("feature_select");
  $featureSelect.innerHTML = '';


  code = activeProject.codeRaw;
  let boardLine = new RegExp(`\/\/MM ${board} ([^\n]*)`);
  var featuresMatch = code.match(boardLine);
  if (!featuresMatch) return;
  featuresMatch = featuresMatch[1].trim();
  var trimmedMatch = featuresMatch.slice(1, -1);
  var features = trimmedMatch.split(', ');
  activeProject.availableFeatures = features;

  featureFill();

  curateCode();
}

function selectFeature(e){
  if (e.checked)
    activeProject.activeFeatures.push(e.name);
  else
    activeProject.activeFeatures = activeProject.activeFeatures.filter(function(item) {
      return item !== e.name;
    });

  curateCode();
}

function codeFetch(path){
  fetch(path)
    .then(res => res.text()
    .then(
      function(rawCode){
        activeProject.codeRaw = rawCode;
        activeProject.codeLines = rawCode.split('\n');

        boardFill();
        featureFill();
        curateCode();
      }
    ));
}

function boardFill(){
  code = activeProject.codeRaw;
  var boardsLine = /\/\/MM BOARDS ([^\n]*)/;
  var boardsMatch = code.match(boardsLine);
  if (!boardsMatch) return false;
  boardsMatch = boardsMatch[1].trim();
  var trimmedMatch = boardsMatch.slice(1, -1);
  var boards = trimmedMatch.split(', ')

  activeProject.boards = boards;

  let $boardSelect = $id("board_select");
  $boardSelect.innerHTML = "";
  var $defaultOption = document.createElement("option");
  $defaultOption.innerHTML = "Select a Board";
  $defaultOption.setAttribute("hidden", "");
  $defaultOption.setAttribute("disabled", "");
  $defaultOption.setAttribute("selected", "");
  $defaultOption.setAttribute("value", "");
  $boardSelect.append($defaultOption);
  for (var i=0; i<boards.length; i++){
    var tBoard = boards[i];
    var $board = document.createElement("option");
    $board.id = "board_"+tBoard;
    $board.innerHTML = tBoard;

    $boardSelect.append($board);
  }
}

function featureFill(){
  var code = activeProject.codeRaw;
  let featuresLine = /\/\/MM FEATURES ([^\n]*)/; 
  let featuresMatch = code.match(featuresLine);
  if (!featuresMatch) return false;
  featuresMatch = featuresMatch[1].trim();

  let trimmedMatch = featuresMatch.slice(1, -1);
  let features = trimmedMatch.split(', ');

  // console.log(features);
  activeProject.features = features;

  let $featureSelect = $id("feature_select");
  $featureSelect.innerHTML = '';
  for (var i=0; i<features.length; i++){
    var tFeature = features[i];
    var $feature = document.createElement("input");
    $feature.setAttribute("type", "checkbox");
    $feature.setAttribute("name", tFeature);
    if (!activeProject.availableFeatures.includes(tFeature))
      $feature.setAttribute("disabled", true);
    $feature.setAttribute("onchange", "selectFeature(this)");
    var $label = document.createElement("label");
    $label.innerHTML = tFeature;
    var $br = document.createElement("br");

    $featureSelect.append($feature);
    $featureSelect.append($label);
    $featureSelect.append($br);
  }

}

function curateCode(){
  let curating = [];
  let is_has_flags = [];
  let skipFlag = '';  
  for (var i=0; i<activeProject.codeLines.length; i++){
    let tLine = activeProject.codeLines[i];
    if (tLine.includes("//MM"))
      continue;
    if (tLine.includes("#define MM_IS"))
      continue;
    if (tLine.includes("#define MM_HAS"))
      continue;

    if (skipFlag){
      if (tLine.includes("#endif // MM_HAS_"+skipFlag))
        skipFlag = '';
      if (tLine.includes("#endif // MM_IS_"+skipFlag))
        skipFlag = '';      
      continue;
    }
    if (tLine.includes("#endif // MM_HAS_"))
      continue;
    if (tLine.includes("#endif // MM_IS_"))
      continue;
      

    if (!skipFlag && tLine.includes("#ifdef MM_HAS_")){
      let index = tLine.indexOf('MM_HAS_');
      let feature = tLine.substring(index + 'MM_HAS_'.length).trim();

      if (!activeProject.activeFeatures.includes(feature))
        skipFlag = feature;
      
      continue;
    }

    if (!skipFlag && tLine.includes("#ifdef MM_IS_")){
      let index = tLine.indexOf('MM_IS_');
      let board = tLine.substring(index + 'MM_IS_'.length).trim();
      if (activeProject.activeBoard != board)
        skipFlag = board;
      
      continue;
    } 


    curating.push(tLine);
  }

  activeProject.codeCurated = curating.join('\n');

  $id("code_out").value=activeProject.codeCurated;
}


function initRepo(){
  let $projectSelect = $id("project_select");

  for (var i=0; i<directory.length; i++){
    var tGroup = directory[i];
    console.log(tGroup)
    var $group = document.createElement("optgroup");
    $group.label = tGroup.group;
    
    $projectSelect.append($group);
    
    for (var j=0; j<tGroup.projects.length; j++){
      var tProj = tGroup.projects[j];
      var $proj = document.createElement("option");
      $proj.id = "proj_"+tProj;
      $proj.innerHTML = tProj.replace(/_/g, ' ');

      $group.append($proj);

    }

  }
  
  
  
}
  

function openRaw(){
  const newWindow = window.open('about:blank', '_blank');
  newWindow.document.write(`<pre>${activeProject.codeRaw}</pre>`);
  newWindow.document.title = activeProject.name;
  newWindow.document.close();

}
  
function saveCode(){
  let code = $id("code_out").value;
  let blob = new Blob([code], {type: "text/ino;charset=utf-8"}); 
  let url = URL.createObjectURL(blob);
  let link = document.createElement("a");
  let fileName = activeProject.name.replace(' ', '_');
  link.download = fileName+".ino";
  link.href = url;
  link.click();
}

function copyCode(){
    let code = $id("code_out");
    code.select();
    code.setSelectionRange(0, 99999); // For mobile devices
    navigator.clipboard.writeText(code.value);
    
    alert("Code copied to your clipboard!");
}
