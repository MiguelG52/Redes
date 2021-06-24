import React, { useState } from 'react'

const InputIP = () => {
    const [IP, setIP] = useState('');
    const handleChange = (e) => {
        setIP(e.target.value);
    }

    const getTipoIp = (IP)=>{
        let tipo = '';
        if(IP >= 1 && IP <= 127) tipo = 'A';
        else if(IP >= 128 && IP <=191) tipo = 'B';
        else if(IP >= 192 && IP <=223) tipo = 'C';
        return(tipo);
    }

    function clasificaIP(ip){
        let nuevaIP = ip.split('.');
        console.log(getTipoIp(nuevaIP[0]));
    }

    const handleSubmit = (e) =>{
        e.preventDefault();
        clasificaIP(IP)
    }

    return (
        <div className="flex justify-around gap-10">
            <form 
                onSubmit={handleSubmit}
                className="flex gap-2 items-center"
            >
                <label htmlFor="ip">Dirección ip:</label>
                <input 
                    className="border shadow-lg"
                    value={IP} 
                    onChange={handleChange}
                    type="text" 
                    placeholder="192.168.124.0" 
                    id="ip" 
                    name="ip"/>
                <button className="text-white bg-blue-600 p-3 w-28 rounded-md">Enviar</button>
            </form>
            <div>
                <h2>Clase:</h2>
                <h2>Mascara de subred: </h2>
            </div>
        </div>
    )
}

export default InputIP
