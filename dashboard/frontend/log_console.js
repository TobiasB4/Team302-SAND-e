/*
LOG CONSOLE SECTION
*/

const scrollbox = document.getElementById("scrollbox");

function startLog(){
    //get info from log
    //window.addEventListener("log",updateLog,true);
    for(let i = 0; i< 10; i++){
        updateLog("hello" + i);
    }
}
function updateLog(x){

    var newElement = document.createElement('div');
    newElement.setAttribute('id', String(x));
    newElement.innerHTML = x;

    scrollbox.appendChild(newElement);
}

startLog();