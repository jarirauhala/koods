'use strict'

var cvs = document.getElementById("canvas");
var ctx = cvs.getContext("2d");

// load images

var sheep = new Image();
var bg = new Image();
var dandelion = new Image();
var stone = new Image();

sheep.src = "Pictures/sheep.png";
bg.src = "Pictures/background.jpg";
dandelion.src = "Pictures/dandelion.png";
stone.src = "Pictures/stone.png";

var sheepSize = 100;
var sheepX = 250;
var sheepY = cvs.height-sheepSize;
var stoneSize = 50;
var score = 0;
var dialogOpenFlag = 0;
var correctAnswer = 'A';
var question;

document.addEventListener("keydown",keyPress);

// returns true for correct answer, false for false
function isAnswerCorrect(answer){

    if(correctAnswer === answer){
        return true;
    }
    else{
        return false;
    }
}

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

// moves the sheep either right or left
function keyPress(e){

    // move left
    if (e.keyCode == '37' && sheepX > 0) {
        sheepX -= 25;
    }
    // move right
    else if(e.keyCode == '39' && sheepX < cvs.width - sheepSize){
        sheepX += 25
    }
}

// dialog setup
$(document).ready(function () {
    $('#dialog1').dialog({
        autoOpen: false,
        modal: true,
        height: 100,
        width: 300,
        resizable: false,
        close : function(){
            $("#dialog1").dialog('close');
            dialogOpenFlag = 0;
        },
        buttons: {
            'True' : function(event) {
                if(isAnswerCorrect()){
                    score += 1
                }

                $("#dialog1").dialog('close');
                dialogOpenFlag = 0;
            },

            'False' : function(event) {
                if(isAnswerCorrect()){
                    score += 20;
                }
                $("#dialog1").dialog('close');
                dialogOpenFlag = 0;            }
        }
    });
});

// adds question and answer to dialog, disables sheep movement
async function displayQuestion(){
    document.removeEventListener("keydown",keyPress);

    $("#dialog1").dialog('open');
    dialogOpenFlag = 1;

    // Change questions
    var question = "What is 1+1";
    var answ1 = "2";
    var answ2 = "3";
    correctAnswer = "A";

    $('#question').html(question);
    $('#answer1').html('True: ' + answ1);
    $('#answer2').html('False: ' + answ2);

    while(dialogOpenFlag === 1){
        console.log("Loopin");
        await sleep(200);
    };

    console.log("Question displayed");

    document.addEventListener("keydown",keyPress);
};

var fallingObjects = [];

fallingObjects[0] = {
    x : 0,
    y : 0,
    objType: "stone"
};

// draw images
function draw(){

    ctx.drawImage(bg,0,0);

    for(var i = 0; i < fallingObjects.length; i++){

        if(fallingObjects[i].objType === "stone"){
            ctx.drawImage(stone,fallingObjects[i].x,fallingObjects[i].y, stoneSize, stoneSize);
        }
        else if (fallingObjects[i].objType === "dandelion") {
            ctx.drawImage(dandelion,fallingObjects[i].x,fallingObjects[i].y, stoneSize, stoneSize);
        }
        else{
            console.log("non");
        }

        fallingObjects[i].y++;

        if( fallingObjects[i].y == 100 ){
            var rand = Math.random();
            console.log(rand);

            // 80% of objects spawned are stone
            if(rand < 0.8){
                fallingObjects.push({
                    x : Math.floor(Math.random()*(cvs.width-stoneSize)),
                    y : 0,
                    objType : "stone"
                });
            }
            else{
                fallingObjects.push({
                    x : Math.floor(Math.random()*(cvs.width-stoneSize)),
                    y : 0,
                    objType : "dandelion",
                    questionAskedFlag : 0
                });
            }
        }

        // detect collision
        if(fallingObjects[i].x >= sheepX - stoneSize &&
           fallingObjects[i].x <= sheepX + sheepSize &&
           fallingObjects[i].y >= sheepY - stoneSize &&
           fallingObjects[i].y <= sheepY + sheepSize) {

            if(fallingObjects[i].objType === "stone"){
                location.stop();
            }
            else{
                if(fallingObjects[i].questionAskedFlag === 0 &&
                  dialogOpenFlag === 0){
                    fallingObjects[i].questionAskedFlag = 1;
                    displayQuestion();
                }
            }
           }

        // if(fallingObjects[i].y == cvs.height){
        //     score++;
        // }


    }

    ctx.drawImage(sheep,sheepX,sheepY,sheepSize,sheepSize);

    ctx.fillStyle = "#fff";
    ctx.font = "20px Verdana";
    ctx.fillText("Score : "+score,10,20);

    requestAnimationFrame(draw);

}

draw();
