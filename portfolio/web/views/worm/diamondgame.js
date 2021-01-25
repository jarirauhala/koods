/* This is a game made by Jari Rauhala in autum 2019
 * as part of a school project. This is my first
 * JavaScript game. In the final version the questions
 * are fetched from a database and score is sent to
 * be evaluated.
 *
 * The lamb is moved by arrow keys right or left.
 * The objective is to avoid stones and collect
 * flowers falling from the sky.
 * when hit with a flower, a default question is
 * displayed. Point count is incremented with 
 * correct answer by 20 and by 1 when avoiding a stone.
 *
 */

window.onload = () => {
let cvs = document.getElementById("canvas");
let ctx = cvs.getContext("2d");

let skill_list = document.getElementById("skill_list");

ctx.font = "40px Arial"
ctx.fillStyle = "black";

//ctx.fillStyle = "red";
//ctx.font = "30px Comic Sans MS";
ctx.textAlign = "center";

// as cvs is 800x400, in transformed units it is 20*10
let coordinate_unit = cvs.width/20;

// load images
let bg = new Image();
let arrow = new Image();
let arrow_up = new Image();
let arrow_right = new Image();
let arrow_down = new Image();
let arrow_left = new Image();
let wasd = new Image();
let bird = new Image();

let diamond_blue = new Image();
let diamond_green = new Image();
let diamond_red = new Image();
let diamond_pink = new Image();
let diamond_purple = new Image();
let diamond_white = new Image();
let diamond_yellow = new Image();

let diamond2_blue = new Image();
let diamond2_green = new Image();
let diamond2_red = new Image();
let diamond2_pink = new Image();
let diamond2_purple = new Image();
let diamond2_white = new Image();
let diamond2_yellow = new Image();

//let path = "./"
let path = "/views/"

bg.src = path + "worm/Pictures/background_winter2.jpg";
arrow.src = path + "worm/Pictures/arrow.png";
arrow_up.src = path + "worm/Pictures/arrow_up2.png";
arrow_right.src = path + "worm/Pictures/arrow_right.png";
arrow_down.src = path + "worm/Pictures/arrow_down.png";
arrow_left.src = path + "worm/Pictures/arrow_left.png";
wasd.src = path + "worm/Pictures/wasd.png";
bird.src = path + "worm/Pictures/small_images/bird2.png";

diamond_blue.src = path + "worm/Pictures/small_images/diamond_blue.png";
diamond_green.src = path + "worm/Pictures/small_images/diamond_green.png";
diamond_red.src = path + "worm/Pictures/small_images/diamond_red.png";
diamond_pink.src = path + "worm/Pictures/small_images/diamond_pink.png";
diamond_purple.src = path + "worm/Pictures/small_images/diamond_purple.png";
diamond_white.src = path + "worm/Pictures/small_images/diamond_white.png";
diamond_yellow.src = path + "worm/Pictures/small_images/diamond_yellow.png";

diamond2_blue.src = path + "worm/Pictures/small_images/diamond2_blue.png";
diamond2_green.src = path + "worm/Pictures/small_images/diamond2_green.png";
diamond2_red.src = path + "worm/Pictures/small_images/diamond2_red.png";
diamond2_pink.src = path + "worm/Pictures/small_images/diamond2_pink.png";
diamond2_purple.src = path + "worm/Pictures/small_images/diamond2_purple.png";
diamond2_white.src = path + "worm/Pictures/small_images/diamond2_white.png";
diamond2_yellow.src = path + "worm/Pictures/small_images/diamond2_yellow.png";

document.addEventListener("keydown",keyPress);


// After a food is eaten a new bodypart is added to the snake.
// Bodyparts form the snake. They follow each other in a line.
class Bodypart {
    x;
    y;
    food;

    constructor(x, y, food=null) {
        this.x = x;
        this.y = y;
        this.food = food;
    }

    get x() {
        return this.x;
    }

    get y() {
        return this.y;
    }

    get food() {
        return this.food;
    }

    coordinates() {
        return [this.y, this.x];
    }
}

// Snake is a collection of bodyparts.
class Snake {
    bodyparts = [];
    born = false; // indicating if game has started or not
    direction_last_moved;

    // indicates where the snake is going next. 
    // 0 -> up
    // 1 -> right
    // 2 -> down
    // 3 -> left
    direction = 1;

    constructor() {
        this.bodyparts.push(new Bodypart(coordinate_unit*5 , coordinate_unit*2)); // head
        //this.bodyparts.push(new Bodypart(coordinate_unit, coordinate_unit));
    }

    get direction() {
        return this.direction;
    }

    get born() {
        return this.born;
    }

    get direction_last_moved() {
        return this.direction_last_moved;
    }

    // returns the length of the snake
    length() {
        return this.bodyparts.length;
    }

    is_there_bodypart_in_coordinate(coordinate) {
        let there_is = false;
        this.bodyparts.forEach(bodypart => {
            if (bodypart.x == coordinate[0] && bodypart.y == coordinate[1]) {
                there_is = true;
            }
        });
        return there_is;
    }

    // update all bodypart positions
    // return status code 0 for game over, 1 for food eaten, 2 for neutral
    move() {
        let game_over = false;
        let append = false;
        let head_moved = false;
        let last_position = [];
        let current_position = [];
        let head_new_position = [];
        let food = foods[foods.length - 1];
        this.bodyparts.forEach(bodypart => {
            if (!head_moved) {
                last_position = [bodypart.x, bodypart.y];
                head_new_position = [bodypart.x, bodypart.y];
                if(this.direction == 0) {
                    head_new_position[1] = bodypart.y - coordinate_unit;
                }
                else if(this.direction == 1) {
                    head_new_position[0] = bodypart.x + coordinate_unit;
                }
                else if(this.direction == 2) {
                    head_new_position[1] = bodypart.y + coordinate_unit;
                }
                else if(this.direction == 3) {
                    head_new_position[0] = bodypart.x - coordinate_unit;
                }
               
                if (head_new_position[0] == food.x && head_new_position[1] == food.y) {
                    append = true;

                    let skill_listed = false;

                    for(let i = 0; i<foods.length-1; ++i) {
                        if(foods[i].description === food.description) {
                            skill_listed = true;
                        }
                    }

                    if(!skill_listed) {
                        let table = document.getElementById("skill_list");
                        let row = table.insertRow(0);
                        let cell1 = row.insertCell(0);
                        let cell2 = row.insertCell(1);

                        cell1.style.width = coordinate_unit*1.5 + "px";

                        cell2.innerHTML = food.description;

                        let img = document.createElement('img');
                        img.src = food.img.src;
                        img.style.width = "100%";
                        //img.style.height = cell1.style.width;
                        cell1.appendChild(img);
                    }
            
                    fadeout_skill_description(food);
                }
                if(head_new_position[0] < 0 
                    || head_new_position[1] < 0 
                    || head_new_position[0] >= coordinate_unit * 20 
                    || head_new_position[1] >= coordinate_unit * 10) {
                    // GAME OVER
                    game_over = true;
                }
                else if(this.is_there_bodypart_in_coordinate(head_new_position)) {
                    // GAME OVER
                    game_over = true;
                }

                bodypart.x = head_new_position[0];
                bodypart.y = head_new_position[1];

                this.direction_last_moved = this.direction;
                
                head_moved = true;
            }
            else {
                current_position = [bodypart.x, bodypart.y]
                bodypart.x = last_position[0];
                bodypart.y = last_position[1];
                last_position = current_position;
            }
        }); 

        if(game_over) {
            return 0;
        }

        if(append) {
            let tail = new Bodypart(last_position[0], last_position[1], food);
            this.bodyparts.push(tail); 
            return 1;
        }
        return 2;
    }

    get bodyparts() {
        return this.bodyparts;
    }

    turn(direction) {
        this.direction = direction;
    }
 
    coordinates_occupied() {
        let coordinates = [];
        let coordinate = [];
        this.bodyparts.forEach(bodypart => {
            coordinate = [bodypart.x, bodypart.y];
            coordinates.push(coordinate);
        })
        return coordinates;
    }
}

// Skills have a description and an image. All skills are stored in all_skills.
// from all_skills a sill is randomly picked for every new food.
class Skill {
    description = "";
    img;

    constructor(description, img) {
        this.description = description;
        this.img = img;
    }

    get description() {
        return this.description;
    }

    get img() {
        return this.img;
    }
}

let all_skills = [
    new Skill("Backend", diamond_blue),
    new Skill("Databases", diamond_green),    
    new Skill("Git", diamond_red),    
    new Skill("Code review", diamond_pink),    
    new Skill("Web dev.", diamond_purple),    
    new Skill("UX approach", diamond_white),    
    new Skill("Eye for UIs", diamond_yellow),
    
    new Skill("Ideation", diamond2_blue),    
    new Skill("Team work", diamond2_green),    
    new Skill("Empathy", diamond2_red),    
    new Skill("Self driven", diamond2_pink),    
    new Skill("Outgoing", diamond2_purple),    
    new Skill("Curiosity", diamond2_white), 
    new Skill("Enthusiasm", diamond2_yellow)    
];

// Food represents a randomized Skill.
// The user tries to eat the new food with Birdie.
class Food {
    x;
    y;

    skill;

    constructor(snake_coordinates) {
        let all_possible_coordinates = [];
        for(let x = 0; x < 20*coordinate_unit; x += coordinate_unit) {
            for(let y = 0; y < 10*coordinate_unit; y += coordinate_unit) {
                all_possible_coordinates.push([x,y]);
            }
        }

        let available_coordinates = [];
        let available;
        all_possible_coordinates.forEach(possible_coordinate => {
            available = true;
            snake_coordinates.forEach(snake_coordinate => {
                if(snake_coordinate[0] == possible_coordinate[0] && snake_coordinate[1] == possible_coordinate[1]) {
                    available = false;
                }
            })
            if(available) {

                available_coordinates.push(possible_coordinate);
            }
        })

        let random_index = Math.floor(Math.random() * (available_coordinates.length-1));
        let random_coordinate = available_coordinates[random_index];

        this.x = random_coordinate[0];
        this.y = random_coordinate[1];

        // randomize skill
        this.skill = all_skills[Math.floor(Math.random() * (all_skills.length))];
    }

    get x() {
        return this.x;
    }

    get y() {
        return this.y;
    }

    say_hello() {
        return "HEllo from food";
    }

    get img() {
        return this.skill.img;
    }

    get description() {
        return this.skill.description;
    }

}

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

snake = new Snake();

// key press event
// moves the bird up(0), right(1), down(2) or left(3)
function keyPress(e){
    let direction_last_moved = snake.direction_last_moved;

    // move up
    if (e.keyCode == '87' && direction_last_moved != 2) {
        snake.turn(0);
        snake.born = true;
    }
    // move right
    else if(e.keyCode == '68' && direction_last_moved != 3){
        snake.turn(1);
        snake.born = true;
    }
    // move down
    else if(e.keyCode == '83' && direction_last_moved != 0){
        snake.turn(2);
        snake.born = true;
    }
    // move left
    else if(e.keyCode == '65' && direction_last_moved != 1){
        snake.turn(3);
        snake.born = true;
    }
}

// mouse click event
// moves the bird up(0), right(1), down(2) or left(3)
// and reacts to new game button
function mouseClickUpdateDirection(canvas, event) { 
    
    let rect = canvas.getBoundingClientRect(); 
    let rect_width = rect.right - rect.left;
    let rect_height = rect.bottom - rect.top;
    let x = event.clientX - rect.left; 
    let y = event.clientY - rect.top; 
    let x_adjusted = 20*coordinate_unit*x/rect_width;
    let y_adjusted = 10*coordinate_unit*y/rect_height;

    // new game button
    if(game_ended) {
        if(x_adjusted >= (7*coordinate_unit-5)
        && x_adjusted <= (13*coordinate_unit+5)
        && y_adjusted >= (7*coordinate_unit-5)
        && y_adjusted <= (8.5*coordinate_unit+5)) {
            start();
        }
    }

    // click outside canvas for some reason registered
    if(x<0 || y<0 || x_adjusted > 20*coordinate_unit || y_adjusted > 10*coordinate_unit) {
        return;
    }
    snake.born = true;
    let direction_last_moved = snake.direction_last_moved;

    if(y_adjusted > (1/2 * x_adjusted)) {
        if(y_adjusted > (-1/2 * x_adjusted +10*coordinate_unit)) {
            if(direction_last_moved != 0) {
                // move down
                snake.turn(2);
            }
        }
        else if(direction_last_moved != 1) {
            // move left
            snake.turn(3);
        }
    }
    else {
        if(y_adjusted > (-1/2 * x_adjusted +10*coordinate_unit)){
            if(direction_last_moved != 3) {
                // move right
                snake.turn(1);  
            }
        }
        else if (direction_last_moved != 2) {     
            // move up
            snake.turn(0);
        }
    }
} 

cvs.addEventListener("mousedown", function(e) 
{ 
    mouseClickUpdateDirection(cvs, e); 
});

async function start() {
    ctx.drawImage(bg,0,0);
    game_ended = false;

    // clear skill list from ui
    let table = document.getElementById("skill_list");
    table.innerHTML = "";
    
    snake = new Snake();
    foods = [];
    foods.push(new Food(snake.coordinates_occupied()));

    await sleep (2000);

    draw();
}

function end_game() {

    ctx.clearRect(0, 0, cvs.width, cvs.height);
    ctx.drawImage(bg,0,0);

    let xhr = new XMLHttpRequest();
    game_ended = true;
    let score = foods.length-1;

    xhr.addEventListener('load', () => {
      let high_score = xhr.response;

      if(score > high_score) {
        ctx.font = "30px Arial"
        ctx.fillText("Game Over!", cvs.width/2, coordinate_unit);  
        ctx.font = "40px Arial"
        ctx.fillText("New High Score: " + high_score + "!!", cvs.width/2, 2*coordinate_unit);  

        // update high score
        let password = "JerusaleminPalmu2020";
        let xhr2 = new XMLHttpRequest();
        let body = password + String(score);
        let params = {
            "msgg":body
          }
        xhr2.open('POST', wholePath);
        xhr2.setRequestHeader("Content-Type", "application/json;charset=UTF-8");

        xhr2.onreadystatechange = function() { // Call a function when the state changes.
            if (this.readyState === XMLHttpRequest.DONE && this.status === 200) {
                // Request finished. Do processing here.
                console.log(xhr2.responseText);
            }
            else {
                console.log("uncool response", xhr2.responseText);
            }
        }

        xhr2.send(JSON.stringify(params));
        end_game();

      }
      else {
        let message2 = "Score: " + String(foods.length -1);
        let message3 = "Worldwide High Score: " + String(high_score);

        // btn border
        ctx.beginPath();
        ctx.fillStyle = "#f8edef";
        ctx.fillRect(7*coordinate_unit-5, 7*coordinate_unit-5, 6*coordinate_unit+10, 1.5*coordinate_unit+10);
        ctx.stroke();

        // inside
        ctx.beginPath();
        ctx.fillStyle = "#7b230b";
        ctx.fillRect(7*coordinate_unit-3, 7*coordinate_unit-3, 6*coordinate_unit+6, 1.5*coordinate_unit+6);
        ctx.stroke();

        // text
        ctx.fillStyle = "#f8edef";
        ctx.fillText("New Game", cvs.width/2, 8*coordinate_unit+4);
        
        ctx.fillStyle = "black";
        ctx.font = "30px Arial"
        ctx.fillText("Game Over!", cvs.width/2, coordinate_unit);  
        ctx.fillText(message2, cvs.width/2, 2*coordinate_unit);  
        ctx.fillText(message3, cvs.width/2, 3*coordinate_unit);  
        
      }
      ctx.font = "25px Arial";
      ctx.fillText("If you can think of something where my skills could be put in use,", cvs.width/2, 4.5*coordinate_unit);  
      ctx.fillText("let's make an appointment!", cvs.width/2, 5.2*coordinate_unit);  
      ctx.fillText("You can find my contact information at the Contact tab.", cvs.width/2, 5.9*coordinate_unit);  
      ctx.font = "40px Arial";
    })

    const url = window.location.hostname;
    const wholePath = 'https://' + url + '/secretpathforhighscore';  
    xhr.open('GET', wholePath);
    xhr.send();
}

// has all eaten and non eaten foods
// non eaten food is last
foods = [];
game_ended = false;

function draw_snake() {
    let head_flag = false;
    snake.bodyparts.forEach(bodypart => {
        if (!head_flag) {
            ctx.drawImage(bird,bodypart.x,bodypart.y,coordinate_unit,coordinate_unit);
            head_flag = true;
        }
        else { // draw body
            ctx.drawImage(bodypart.food.img,bodypart.x+0.2*coordinate_unit,bodypart.y+0.2*coordinate_unit,coordinate_unit*0.8,coordinate_unit*0.8);
        }
    })
}

function fadeout_skill_description(food) {
    let x_to_draw = food.x;
    let y_to_draw = food.y;
    let alpha = 1.0,   // full opacity
        interval = setInterval(function () {
            ctx.clearRect(0, 0, cvs.width, cvs.height);
            ctx.drawImage(bg,0,0);
            draw_snake();
            draw_food();

            ctx.fillStyle = "rgba(0, 0, 0, " + alpha + ")";

            if(food.y < coordinate_unit) {
                y_to_draw = food.y + 2*coordinate_unit;
            }
            if(food.x > 16*coordinate_unit) {
                x_to_draw = food.x-2*coordinate_unit
            }
            if(food.x < 3*coordinate_unit) {
                x_to_draw = 3*coordinate_unit
            }

            ctx.fillText(food.description, x_to_draw, y_to_draw);

            ctx.strokeStyle = "#00000";
            ctx.fillStyle = "#00000";

            alpha = alpha - 0.1; // decrease opacity (fade out)
            if (alpha < 0) {
                ctx.clearRect(0, 0, cvs.width, cvs.height);
    
                clearInterval(interval);
                ctx.drawImage(bg,0,0);
                draw_snake();
                draw_food();

                }
        }, 50); 
}

function draw_food() {
    let food = foods[foods.length -1];
    ctx.drawImage(food.img,food.x,food.y,coordinate_unit*1.1,coordinate_unit*1.1);
}

// draw images
async function draw(){

    ctx.drawImage(bg,0,0);

    draw_snake();
    draw_food();

    // draw instructions
    if(!snake.born) {
        let hilight_counter = 0;
        
        while(!snake.born) {
            ctx.clearRect(0, 0, cvs.width, cvs.height);
            ctx.drawImage(bg,0,0);
            draw_snake();


            if(hilight_counter == 0) {
                ctx.clearRect(0, 0, cvs.width, cvs.height);
                ctx.drawImage(bg,0,0);
                draw_snake();

                ctx.fillText("Gather my skills with Birdie", cvs.width/2, cvs.height/2);
                hilight_counter++;
                await sleep(1000);
            }

            else if(hilight_counter == 1) {
                ctx.clearRect(0, 0, cvs.width, cvs.height);
                ctx.drawImage(bg,0,0);
                draw_snake();

                ctx.fillText("Control with WASD keys", cvs.width/2, cvs.height/2 - coordinate_unit);
                ctx.drawImage(wasd, cvs.width/2-2*coordinate_unit, cvs.height/2, coordinate_unit*4, coordinate_unit*4);

                hilight_counter++;
            }

            
            else if(hilight_counter == 2) {
                ctx.clearRect(0, 0, cvs.width, cvs.height);
                ctx.drawImage(bg,0,0);
                draw_snake();

               ctx.fillText("Or by clicking the screen", cvs.width/2, cvs.height/2);

                // draw arrows
                ctx.drawImage(arrow_down,cvs.width/2-coordinate_unit, cvs.height-3*coordinate_unit, coordinate_unit*2, coordinate_unit*2);
                ctx.drawImage(arrow_up,cvs.width/2-coordinate_unit, coordinate_unit, coordinate_unit*2, coordinate_unit*2);
                ctx.drawImage(arrow_right,cvs.width-3*coordinate_unit, cvs.height/2-coordinate_unit, coordinate_unit*2, coordinate_unit*2);
                ctx.drawImage(arrow_left,coordinate_unit, cvs.height/2-coordinate_unit, coordinate_unit*2, coordinate_unit*2);

                hilight_counter++;
            }

            else if(hilight_counter == 3) {
                ctx.clearRect(0, 0, cvs.width, cvs.height);
                ctx.drawImage(bg,0,0);
                draw_snake();

                ctx.fillText("Start by moving to any direction!", cvs.width/2, cvs.height/2);

                hilight_counter = 0;
            }

            await sleep(3000);
        }

        ctx.clearRect(0, 0, cvs.width, cvs.height);
        ctx.drawImage(bg,0,0);
        draw_snake();

        ctx.fillText("Get ready!", cvs.width/2, cvs.height/2);
        await sleep(1000);

        ctx.clearRect(0, 0, cvs.width, cvs.height);
        ctx.drawImage(bg,0,0);
        draw_snake();

        ctx.fillText("GO!", cvs.width/2, cvs.height/2);
    }

    await sleep(500);

    let status_code = snake.move();
    if(status_code == 1) { // food eaten
        let new_food = new Food(snake.coordinates_occupied());
        foods.push(new_food);
    }

    if(status_code != 0) {
        requestAnimationFrame(draw);
    }
    else {
        end_game();
    }

}
    start();
}