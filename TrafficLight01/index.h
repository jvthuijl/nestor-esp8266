const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="nl">
<head>
    <title>PartyKiwi Traffic Light</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta charset="utf-8">
    <style>
        html, body {
            background-color: #eee;
            margin: 0;
            padding: 0;
        }

        .pkimg {
            width: 100px;
            height: 66px;
            margin: 0 auto;
        }

        .container {
            font-family: Arial, Helvetica, sans-serif;
            font-size: 20px;
            max-width: 420px;
            margin: 20px auto;
            padding: 20px;
            border: 1px #ddd solid;
            background-color: #fff;
            text-align: center;
        }

        .tt {
            font-size: 50px;
            font-weight: bold;
            color: #18be2b;
            display: block;
            margin: 5px;
            text-transform: uppercase;
        }

        .smalltext {
            font-size: 12px;
            color: #777;
        }

        .box {
            padding: 10px;
        }

        .button {
            display: inline-block;
            margin: 4px;
            padding: 12px 36px;
            text-decoration: none;
            color: #fff;
            background-color: #eee;
            border-radius: 20px;
            word-wrap: break-word;
            width: 100px;
            cursor: pointer;
        }

        .red {
            background-color: red;
        }

        .green {
            background-color: green;
        }

        @media (max-width: 500px) {
            html, body {
                background: #fff;
            }

            .container {
                border: none;
                margin: 0 auto;
            }
        }
    </style>
</head>
<body>
    <div class="container center">
        <div id="buttonbox">
            <div class="box"><a id="roodButton" class="button red">Rood</a></div>
            <div class="box"><a id="groenButton" class="button green">Groen</a></div>
        </div>
        <div class="box">
            <img alt="PartyKiwi" src="data:image/png;base64,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" />
            <p id="statustext" class="smalltext">Powered by PartyKiwi</p>
        </div>
    </div>
    <script>
        document.addEventListener('DOMContentLoaded', Init);

        function Init() {
            AddClickEvent('#roodButton', function () {
                SetColor('rood');
            });
            AddClickEvent('#groenButton', function () {
                SetColor('groen');
            });
        }

        function SetColor(color) {
            Ajax('/' + color, function () {
                SetStatus(color);
            });
        }

        function AddClickEvent(id, fn) {
            var el = document.querySelector(id);
            if (el) el.addEventListener('click', function (e) {
                fn(e);
            });
        }

        function SetStatus(text) {
            var el = document.querySelector('#statustext');
            if (el) {
                el.textContent = text;
            }
        }

        function Spinner() {
            var div = document.createElement('div');
            div.id = 'spinner';
            return div;
        }

        function Ajax(uri, callback) {
            var request = new XMLHttpRequest();
            request.open('GET', uri, true);
            request.onload = function () {
                var text = '';
                if (request.status == 200) {
                    text = request.responseText;
                } else {
                    text = 'Server geeft foutcode ' + request.status;
                }
                if (callback) {
                    callback(text);
                }
            };
            request.onerror = function () {
                if (callback) {
                    callback('Fout bij aanroepen api! Probeer opnieuw.');
                }
            };
            request.send(null);
        }


    </script>
</body>
</html>
)=====";