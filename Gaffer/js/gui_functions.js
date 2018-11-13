
var DUMMY_deleteClick = document.querySelectorAll(".notification button.delete")

Array.from(DUMMY_deleteClick).forEach(link => {
    link.addEventListener('click', function(event) {
        console.info(event);
    });
});

function GUI_show_error(text)
{
    document.querySelector("#notification-error").classList.remove("is-hidden-tablet");
    document.querySelector("#error-text").innerText  = text;
}