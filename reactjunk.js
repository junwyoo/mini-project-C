import React from 'react';
import ReactDOM from 'react-dom';

function downloadFile(filename, data){
  var element = document.createElement("a");
  var file = new Blob([data], {type: 'json/plain'});
  element.href = URL.createObjectURL(file);
  if(filename === ""){
    filename = `NoName`;
  }
  element.download = `${filename}.json`;
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
          <input placeholder="toolOpt1" style={{width:"10%"}} id={i+'_toolOpt1'} />
          <input placeholder="toolOpt2" style={{width:"10%"}} id={i+'_toolOpt2'} />
          <input placeholder="toolOpt3" style={{width:"10%"}} id={i+'_toolOpt3'} />
          <input placeholder="toolOpt4" style={{width:"10%"}} id={i+'_toolOpt4'} />
          <input placeholder="toolOpt5" style={{width:"10%"}} id={i+'_toolOpt5'} />
          <input placeholder="toolOpt6" style={{width:"10%"}} id={i+'_toolOpt6'} />
          <input placeholder="toolCRC" style={{width:"10%"}} id={i+'_toolCRC'} />
          <input placeholder="AreaOpt" style={{width:"10%"}} id={i+'_AreaOpt'} />
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
      for (let i = n; i<this.state.inputSize-1; i++){
        document.getElementById(`${i}_suffix`).value = document.getElementById(`${i+1}_suffix`).value;
        document.getElementById(`${i}_toolOpt1`).value = document.getElementById(`${i+1}_toolOpt1`).value;
        document.getElementById(`${i}_toolOpt2`).value = document.getElementById(`${i+1}_toolOpt2`).value;
        document.getElementById(`${i}_toolOpt3`).value = document.getElementById(`${i+1}_toolOpt3`).value;
        document.getElementById(`${i}_toolOpt4`).value = document.getElementById(`${i+1}_toolOpt4`).value;
        document.getElementById(`${i}_toolOpt5`).value = document.getElementById(`${i+1}_toolOpt5`).value;
        document.getElementById(`${i}_toolOpt6`).value = document.getElementById(`${i+1}_toolOpt6`).value;
        document.getElementById(`${i}_toolCRC`).value = document.getElementById(`${i+1}_toolCRC`).value;
        document.getElementById(`${i}_AreaOpt`).value = document.getElementById(`${i+1}_AreaOpt`).value;
        newInputs[i] = i;
      }
      this.state.inputs.pop();
      this.setState({inputSize: this.state.inputSize-1});
      this.setState({ inputs: newInputs});
    }

    shuffleAndAppend(n) {

      let res = '\n\t\t{\n\t\t\t"suffix":"'
        + document.getElementById(`${n}_suffix`).value + '",\n\t\t\t'
        + '"options":["'
        + document.getElementById(`${n}_toolOpt6`).value+'", "", "'
        + document.getElementById(`${n}_AreaOpt`).value+'", "'
        + document.getElementById(`${n}_toolOpt2`).value+'", "'
        + document.getElementById(`${n}_toolCRC`).value+'", "'
        + document.getElementById(`${n}_toolOpt5`).value+'", "'
        + document.getElementById(`${n}_toolOpt1`).value+'", "'
        + document.getElementById(`${n}_toolOpt3`).value+'", "", "'
        + document.getElementById(`${n}_toolOpt4`).value+'", ""]\n\t\t}';

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

ReactDOM.render(
  <MultipleChoice />,
  document.getElementById('root')
);
