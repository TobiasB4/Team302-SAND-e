/*
ACTIONS SECTION -> SET HOME AND RETURN HOME
*/

function setHome(){
    var input = prompt("Please enter home coordinates:","[49.28451838370452, -123.14407949644797]");
    var text;
    if(input == null || input == ""){
        text = "Invalid input";
    }else{
        text = input;
    }
    //Replace console log with some server interaction
    console.log(text);
}