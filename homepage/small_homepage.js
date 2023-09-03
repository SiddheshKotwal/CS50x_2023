document.addEventListener('DOMContentLoaded', function(){

    var close = document.querySelector('.nav-list');
    var closeButton = document.querySelector('.fa-times');
    var openButton = document.querySelector('.fa-bars');

    hideMenu();

    function hideMenu(){
        close.style.display = 'none';
    };

    function openMenu(){
        close.style.display = '';
    };

    closeButton.addEventListener('click', hideMenu);
    openButton.addEventListener('click', openMenu);

    var typed = new Typed('#typedText', {
        strings: ['Software Engineer', 'Web Developer'],
        typeSpeed: 130,
        backSpeed: 50,
        loop: true
    });

    setTimeout(() => {
        var element = document.querySelector('.greet');
        element.classList.remove('greet');
        element.classList.add('greetOut');
    }, 10000);

    var navbar =  document.querySelector('nav');

    window.addEventListener('scroll', function() {
        var scroll = window.scrollY;

        if(scroll > 0)
        {
            navbar.classList.remove('navbar');
            navbar.classList.add('new_navbar');
        }
        else
        {
            navbar.classList.remove('new_navbar');
            navbar.classList.add('navbar');
        }
    })

    const observer = new IntersectionObserver((entries) => {
        entries.forEach((entry) => {
            console.log(entry)
            if (entry.isIntersecting) {
                entry.target.classList.add('show');
            } else {
                entry.target.classList.remove('show');
            }
        });
    });

    const hiddenElementsX = document.querySelectorAll('.hiddenX');
    const hiddenElementsY = document.querySelectorAll('.hiddenY');
    hiddenElementsX.forEach((el) => observer.observe(el));
    hiddenElementsY.forEach((el) => observer.observe(el));

    var1 = document.querySelector('.myPhoto').classList.remove('hiddenX');
    var2 = document.querySelector('.myDetails').classList.remove('hiddenX');
    var3 = document.querySelector('#skill_div').classList.remove('hiddenY');

    function handleIntersect(entries, observer) {
        entries.forEach(entry => {
            if (entry.isIntersecting) {
                // Element is visible, run your desired function here
                progresses();
            }
        });
    }
  
    // Create an instance of the Intersection Observer
    const observers = new IntersectionObserver(handleIntersect);

    // Select the target element
    const target = document.querySelector('.circular_progress');

    // Start observing the target element
    observers.observe(target);

    let projects = document.querySelector(".project_5");

      projects.addEventListener("click", function(){
        window.location.href = 'project_1.html';
      });

      document.getElementById('submit').addEventListener('click', function(){
        console.log('Message Sent!');
      });

});

window.onload = function(){

    var typed = new Typed('.greet', {
        strings: ['Hi there, Thanks for visiting my website! :)'],
        typeSpeed: 40,
        loop: false,
        showCursor: false
    });
}

function progresses(){
    let cir_progress = document.querySelector(".circular_progress");
    let progress = document.querySelector(".progress-value");
    let cir_progress_1 = document.querySelector(".circular_progress_1");
    let progress_1 = document.querySelector(".progress-value_1");
    let cir_progress_2 = document.querySelector(".circular_progress_2");
    let progress_2 = document.querySelector(".progress-value_2");
    let start = 0, start_1 = 0, start_2 = 0,
    final = 80, final_1 = 70, final_2 = 50,
    progress_speed = 20;
    
    let progress_interval = setInterval(() => {
        start++;
        progress.textContent = `${start}%`;
        cir_progress.style.background = `conic-gradient( #144153, ${start * 3.6}deg, #c4c4c4 0deg)`;
        if(start == final){
            clearInterval(progress_interval);
        }
    }, progress_speed);

    let progress_interval_1 = setInterval(() => {
        start_1++;
        progress_1.textContent = `${start_1}%`;
        cir_progress_1.style.background = `conic-gradient( #144153, ${start_1 * 3.6}deg, #c4c4c4 0deg)`;
        if(start_1 == final_1){
            clearInterval(progress_interval_1);
        }
    }, progress_speed);

    let progress_interval_2 = setInterval(() => {
        start_2++;
        progress_2.textContent = `${start_2}%`;
        cir_progress_2.style.background = `conic-gradient( #144153, ${start_2 * 3.6}deg, #c4c4c4 0deg)`;
        if(start_2 == final_2){
            clearInterval(progress_interval_2);
        }
    }, progress_speed);
}