// window.onload = function() { alert("welcome"); };
$(document).ready(function(){
    $("a").click(function(event) {
        //alert("Thanks for visiting!");
        //return false;
        //alert("As you can see, the link no longer took you to jquery.com");
        $(this).addClass("test");
        event.preventDefault();
        alert("As you can see, the link no longer took you to anywhere");
        $(this).hide("slow");
    });
    $("a").hover(function() {
        $(this).addClass("test");
    }, function() {
        $(this).removeClass("test");
    });
    $("p").css("background", "#eee");

    $("#rating").append("Please rate: ");
    for (var i = 1; i < 5; i++) {
        $("#rating").append("<a href='#'>" + i + "</a> ");
    }

    $("#rating a").click(function(e) {
        e.preventDefault();
        alert("rating: " + $(this).text());
        //$.post("rate.php", {rating: $(this).html()}, function(xml) {
        //    // format and output result
        //    $("#rating").html(
        //        "Thanks for rating, current average: " +
        //        $("average", xml).text() +
        //        ", number of votes: " +
        //        $("count", xml).text());
        //});
    });

    $(".article .thebody").hide();
    $("#container .article ul")
        .prepend("<li class='readbody'><a href='' title='Read the article'>Read Body</a></li>");

    $(".actions li.readbody a").click(function(event){
        $(this).parents("ul").prev(".thebody").toggle();

        // Stop the link click from doing its normal thing
        event.preventDefault();
    });
});

function examples() {
    //Example A
    //Get number of paragraphs:
    alert($("div.contentToChange p").size());

    // Example B
    // Animate a paragraph in Column 2 by using a slide animation.
    //
    $("div.contentToChange p.firstparagraph:hidden").slideDown("slow");
    $("div.contentToChange p.firstparagraph:visible").slideUp("slow");


    //Example C
    //Add/Remove text from the end of all <p> elements in column 2 except the paragraph in the red box.
    //
    $("div.contentToChange p:not(.alert)")
        .append("<strong class='addedtext'> This text was just appended to this paragraph</strong>");
        $("strong.addedtext").remove();

    //Example D
    //Remove paragraph with fade and animation.
    //
    $("div.contentToChange p.thirdparagraph").hide("slow");

    //Example E
    //Change the font weight and color of all Italic text in column 2 by adding CSS properties and values to all <em> elements.
    $("div.contentToChange em").css({color:"#993300", fontWeight:"bold"});


    //Example F
    //Change the CSS on the fifth paragraph in Column 2 by adding a class value to the <p> element.
    $("p.fifthparagraph").addClass("changeP");
    $("p.fifthparagraph").removeClass("changeP");
}

var v = function getElements() {
    var elementCount = $("*").css("border","1px dashed lightgray").length;
    $("body").prepend("<h3>" + elementCount + " elements found</h3>");
}();

function event_trigger() {
    var e = jQuery.Event("click");
    $("body").trigger(e);
}

function jquery_selectors() {
    // select all
    // basics
    var all = $("*");
    var elemByClass = $(".class");
    var elemByTagName = $("tag");
    var elemDivs = $("div");
    var elemById = $("#id");
    var elemsMultiSel = $(".class,div,#id");

    // basic filters
    var ani = $("div:animated");
    // :animated :focus
    // :eq() :lt() :gt() :even :odd :first :last :header :not()

    // child filters
    var spans = $("div span:first-child");
    // :first-child :last-child :nth-child :only-child


    // Content filter
    var divHasP = $("div:has(p)");
    // :contains("text")
    // :has("selector")
    // :empty // have no children and text
    // :parent

    // Form
    // :button :checkbox :file :image :input :password :radio :reset :submit :text
    // :disabled :enabled :focus :selected

    // Hierachy
    // Child Selector ("parent > child")
    // Descendant Selector ("ancester descendant")
    // Next adjacent Selector ("prev + next")
    // Next siblings Selector ("prev ~ siblings")
}

