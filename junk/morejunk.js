import React from 'react';
import ReactDOM from 'react-dom';

function downloadFile(filename, data){
  var element = document.createElement("a");
  var file = new Blob([data], {type: 'json/plain'});
  element.href = URL.createObjectURL(file);
  if(filename === ""){
    filename = `NoName`;
  }
  element.download = `${filename}.json`; // backticks ( `)
  element.click();
}


class MultipleChoice extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
          inputSize: 1,
          inputs: Array(1).fill(0)
        };
    }

    renderInputField(i){
      return (
        <React.Fragment>
          <input placeholder="Suffix" style={{width:"10%"}} id={i+'_suffix'} />
          <input placeholder="safesafesafesafe1" style={{width:"10%"}} id={i+'_safesafesafesafe1'} />
          <input placeholder="safesafesafesafe2" style={{width:"10%"}} id={i+'_safesafesafesafe2'} />
          <input placeholder="safesafesafesafe3" style={{width:"10%"}} id={i+'_safesafesafesafe3'} />
          <input placeholder="safesafesafesafe4" style={{width:"10%"}} id={i+'_safesafesafesafe4'} />
          <input placeholder="safesafesafesafe5" style={{width:"10%"}} id={i+'_safesafesafesafe5'} />
          <input placeholder="safesafesafesafe6" style={{width:"10%"}} id={i+'_safesafesafesafe6'} />
          <input placeholder="safechecksum" style={{width:"10%"}} id={i+'_safechecksum'} />
          <input placeholder="saferegion" style={{width:"10%"}} id={i+'_saferegion'} />
          <button onClick={ () => this.removeOne(i)}>
              -
          </button>
       </React.Fragment>
     );
    }

    render() {
        return(
            <div>
                    Model Name: <input placeholder="Model" id="model" />
                    <div>
                      <br></br>
                       {this.state.inputs.map(input=>
                         this.renderInputField(input)
                       )}
                    </div>
               <button onClick={ () => this.addMore() }>
                   +
               </button>
               <br></br>
               <button onClick={ () => this.handleDownload()}>
                 Download
               </button>
            </div>
        );
    }


    // // ..TODO parsing string

    addMore() {
        var newInput = this.state.inputSize;
        this.setState({inputSize: this.state.inputSize+1});
        this.setState({ inputs: this.state.inputs.concat(newInput) });
    }
    removeOne(n) {
      var newInputs = this.state.inputs;
      for (let i = n; i<this.state.inputSize-1; i++){ // backticks... everywhere
        document.getElementById(`${i}_suffix`).value = document.getElementById(`${i+1}_suffix`).value;
        document.getElementById(`${i}_safesafesafesafe1`).value = document.getElementById(`${i+1}_safesafesafesafe1`).value;
        document.getElementById(`${i}_safesafesafesafe2`).value = document.getElementById(`${i+1}_safesafesafesafe2`).value;
        document.getElementById(`${i}_safesafesafesafe3`).value = document.getElementById(`${i+1}_safesafesafesafe3`).value;
        document.getElementById(`${i}_safesafesafesafe4`).value = document.getElementById(`${i+1}_safesafesafesafe4`).value;
        document.getElementById(`${i}_safesafesafesafe5`).value = document.getElementById(`${i+1}_safesafesafesafe5`).value;
        document.getElementById(`${i}_safesafesafesafe6`).value = document.getElementById(`${i+1}_safesafesafesafe6`).value;
        document.getElementById(`${i}_safechecksum`).value = document.getElementById(`${i+1}_safechecksum`).value;
        document.getElementById(`${i}_saferegion`).value = document.getElementById(`${i+1}_saferegion`).value;
        newInputs[i] = i;
      }
      this.state.inputs.pop();
      this.setState({inputSize: this.state.inputSize-1});
      this.setState({ inputs: newInputs});
    }

    shuffleAndAppend(n) {
      let res = 'this is safe, no hashing here'
      + document.getElementById(`${n}_suffix`).value + '",\n\t\t\t'
      + '"options":["'
      + document.getElementById(`${n}_safesafesafesafe1`).value+'", "", "'; // just the first element
      return res;
    }

    handleDownload = () => {
      let len = this.state.inputs.length;
      let inputArr = this.state.inputs;
      let res = "";
      let isValid = Array.apply(null, Array(len)).map(Number.prototype.valueOf,0);

      for(let i=0; i<len; i++){
        if(document.getElementById(`${i}_suffix`).value === ""){
          continue;
        }
        isValid[i] = 1;
      }

      res = '{\n\t"suffixes":[';

      let isFirst = true;
      for(let i=0; i<len; i++){
        if(isValid[i]){
          if(i !== 0 && !isFirst){
            res += ",";
          }
          res += this.shuffleAndAppend(inputArr[i]);
          isFirst = false;
        }
      }

      res += '\n\t]\n}'

      //download file
      downloadFile(document.getElementById(`model`).value, res);
    }
  }

ReactDOM.render( // the main render for this one-page site
  <MultipleChoice />,
  document.getElementById('root')
);
