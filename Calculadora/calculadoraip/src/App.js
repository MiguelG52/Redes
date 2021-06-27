import InputIP from './components/inputIP';
import './App.css';
import { useState } from 'react';

function App() {
  const [IP, setIP] = useState('');
  const [Tipo, setTipo] = useState('');
  const [MascaraRed, setMascaraRed] = useState('');
  const [TipoSubRed, setTipoSubred] = useState('');
  const [nTipoS, setnTipoS] = useState(0);

  return (
    <div className="flex flex-col items-center h-screen w-screen gap-5 bg-gray-200">
      <h1>Calculadora IP</h1>
      <div>
        <InputIP
          IP={IP}
          setIP={setIP}
          Tipo={Tipo}
          setTipo={setTipo}
          MascaraRed = {MascaraRed}
          setMascaraRed = {setMascaraRed}
          TipoSubNet = {TipoSubRed}
          setTipoSubNet = {setTipoSubred}
          nTipoS = {nTipoS}
          setnTipoS = {setnTipoS}
        />
      </div>
      
    </div>
  );
}

export default App;
