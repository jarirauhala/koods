import React from 'react';
import logo from './kimonoJari.png';
import './App.css';
import Cookies from 'universal-cookie';

function App() {
  return (
    <div className="App">
      <header id="App-header">
        Welcome!
      </header>
      <body className="App-body">
        <div className="keho">
          <p className="messageBoard">This is Nappipeli made by Jari Rauhala.</p>
          <p className="messageBoard">And this is a picture of me in a kimono: </p>
          <img src={logo} className="App-logo" alt="logo" />
          <button id="playButton" onClick={playClicked}>        
            Play!
          </button>
          <p id="pointDisplay"></p>
        </div>
      </body>
    </div>
  );
}

export default App;

// cookie holds the points for a player
const cookie = new Cookies();

function updateHeaderText(message) {
  document.getElementById("App-header").innerHTML = message;
}

// updates points when the page is loaded
document.addEventListener('DOMContentLoaded', (event) => {
  updatePoints();
})

// visualizes player's point count with information from cookie
function updatePoints() {
  const playerPoints = cookie.get('points');
  document.getElementById("pointDisplay").innerHTML = "points: " + playerPoints;
}

// updates the cookie after play
// i.e. takes a point and adds winnings
function registerWinnings(winnings) {
  var oldPoints = cookie.get('points');
  var newPoints = oldPoints - 1 + winnings;

  cookie.set('points', newPoints);
  updatePoints();

  if(newPoints === 0) {
    updateHeaderText("Game over!")
    document.getElementById("playButton").innerHTML = ":(";
  }
}

// checks if the counter value provides the player any points
// returns the points won if any
// and 0 if not, obviously
function assessWinnings(count) {
  if(count % 250 === 0){
    updateHeaderText("You won 250 points!")
    return 250;
  }
  if (count % 100 === 0) {
    updateHeaderText("You won 40 points!")
    return 40;
  }
  if(count % 10 === 0) {
    updateHeaderText("You won 5 points!")
    return 5;
  }
  else {
    // resolve how many clicks away is the next win
    var nextWin = count;
    for(let i=0; i<10; i++) {
      console.log()
      if(nextWin % 10 === 0) {
        if(i === 1){
          updateHeaderText("No luck! Next win is " + i + " click ahead!");
        }
        else {
          updateHeaderText("No luck! Next win is " + i + " clicks ahead!");
        }
      }
      nextWin++;
    }
    
    return 0;
  }
}

// called when clicked the play button
// send a get request to /play to get the value of the counter
function playClicked() {

  var playerPoints = cookie.get('points');

  if (playerPoints > 0) {

    var counter = "-1";
    var xhr = new XMLHttpRequest();
    xhr.addEventListener('load', () => {
      counter = xhr.response;
      const winnings = assessWinnings(counter);
      registerWinnings(winnings);
    })

    const url = window.location.href;
    const wholePath = url + 'secretpathforcounterfetching';  
    xhr.open('GET', wholePath);
    xhr.send();
  }


}

// checks for cookes and creates new if none exists.
// .get('points') returns undefined if points not set
// i.e. cookie is not set
if(cookie.get('points') >= 0) { 
  console.log("cookie exists already, points: " + cookie.get('points'));
}
else{
  console.log("cookie NOT set, points: " + cookie.get('points'));
  cookie.set('points', '20', {
    path: '/', 
    expires: new Date(Date.now()+86400)});
}