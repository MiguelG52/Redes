import InputIP from './components/inputIP';
import './App.css';

function App() {
  return (
    <div className="flex flex-col items-center h-screen w-screen gap-5">
      <h1>Calculadora IP</h1>
      <div>
        <InputIP/>
      </div>
      
    </div>
  );
}

export default App;
