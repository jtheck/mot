



function Project(){

  this.name = '';
  this.boards = [];
  this.features = [];

  this.activeBoard = '';
  this.activeFeatures = [];

  this.rawCode = '';
  this.boardCurated = '';
  this.featureCurated = '';
}

let activeProject = new Project();

function Feature(){
  this.name = '';
  this.boards = [];
}




let directory = [
  {
    group:'Miscellaneous',
    projects:[
        'Hello_World',
        'Hourglass'
    ]
  },
  {
    group:'Mot.Moe',
    projects:[
        'TamagoMoMo',
        'Mot.moe'
    ]
  }
];
  
  
function saveCode(){
  let code = $id("code_out").value;
  let blob = new Blob([code], {type: "text/ino;charset=utf-8"}); 
  console.log(blob)
  let url = URL.createObjectURL(blob);
  let link = document.createElement("a");

  link.download = "test.ino";
  link.href = url;
  link.click();
}

function copyCode(){
    // Get the text field
    let code = $id("code_out");

    // Select the text field
    code.select();
    code.setSelectionRange(0, 99999); // For mobile devices
  
      // Copy the text inside the text field
    navigator.clipboard.writeText(code.value);
    
    alert("Code copied to your clipboard!");
}







  
var selectProject = function(e){
  let $projectSelect = $id("project_select");
  let val = $projectSelect.value;
  let $project = $id("proj_"+val.replace(' ', '_'));
  
  let project = val.replace(' ', '_');
  let group = $project.parentElement.label; 
  let folder = 'repo/'+group+'/'+project+'/';

  let path = folder+project+'.ino';

  let $logoCell = $id("project_logo");
  let $projectLogo = document.createElement("img");
  $projectLogo.src = folder+"logo.png";
  $logoCell.innerHTML = "";
  $logoCell.append($projectLogo);



  codeFill(path);
}


let codeFill = function(path){

  let balls = fetch(path)
    .then(res => res.text()
    .then(
      function(rawCode){

        var removeMM = /\/\/MM.*?\n/g;
        let cleanCode = rawCode.replace(removeMM, '');
        $id("code_out").value=cleanCode;
        


        boardFill(rawCode);
        featureFill(rawCode);

      }
    ));

}

let boardFill = function(code){
  
  var boardsLine = /\/\/MM BOARDS ([^\n]*)/;
  var boardsMatch = code.match(boardsLine)[1];
  if (!boardsMatch) return false;
  
  var trimmedMatch = boardsMatch.slice(1, -1);
  var boards = trimmedMatch.split(', ')

  console.log(boards);


  let $boardSelect = $id("board_select");
  $boardSelect.innerHTML = "";
  
  for (var i=0; i<boards.length; i++){
    var tBoard = boards[i];
    var $board = document.createElement("option");
    $board.id = "board_"+tBoard;
    $board.innerHTML = tBoard;

    $boardSelect.append($board);
  }


  
  let $imageCell = $id("project_board");
  let $boardImage = document.createElement("img");
  $boardImage.src = "wat/u.png";
  $imageCell.innerHTML = "";
  $imageCell.append($boardImage);

}

let featureFill = function(code){
  let featuresLine = /\/\/MM FEATURES ([^\n]*)/; 
  let featuresMatch = code.match(featuresLine)[1];
  if (!featuresMatch) return false;

  let trimmedMatch = featuresMatch.slice(1, -1);
  let features = trimmedMatch.split(', ');

  console.log(features);


}




var initRepo = function(){
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
  