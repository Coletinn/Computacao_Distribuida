from flask import Flask
from flask import jsonify
import urllib.request, json

app = Flask(__name__)

@app.route('/',methods=['GET'])
def status():
    return "Maquina 1"

@app.route('/convertemoeda/<valor>',methods=['GET'])
def realizaConversao(valor):
    url = "https://economia.awesomeapi.com.br/json/last/BRL-USD,BRL-EUR"
    response = urllib.request.urlopen(url)
    dados = response.read()
    dict = json.loads(dados)
    dolar = dict["BRLUSD"]["low"]
    euro = dict["BRLEUR"]["low"]
    moedaJson = {
        'conversao': {
            'real': valor,
            'dolar': f'{float(dolar)*int(valor):.2f}',
            'euro': f'{float(euro)*int(valor):.2f}'
        }
    }
    return jsonify(moedaJson)
    

if __name__ == '__main__':
 app.run(host='0.0.0.0')

