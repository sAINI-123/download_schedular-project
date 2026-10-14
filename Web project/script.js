document.getElementById("year").textContent  = new date().getFullYear();

const roles= [
    "web Devloper",
    "Creative Designer",
    "Tech Enthusiast"

];



let roleIndex= 0;
const typing = document.getElementById("typing");

setInterval(() => {
    roleIndex = (roleIndex + 1) % roles.length;
    typing.style.opacity = 0;

    setTimeout(() =>{
        typing.textContent = roles[roleIndex];
        typing.style.opacity = 1;

    }, 400);
}, 2400);


