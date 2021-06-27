import React from 'react'
import { useState } from 'react';
import { useEffect } from 'react';

const InputIP = ({IP, setIP, Tipo, setTipo, MascaraRed, setMascaraRed, TipoSubNet, setTipoSubNet, nTipoS, setnTipoS}) => {

    const [nSubredes, setnSubredes] = useState(0)
    const [nHost, setnHost] = useState(0)
    const [SubMascara, setSubMascara] = useState('')

    let bitsHost = 0;

    const handleChange = (e) => {
        setIP(e.target.value);
    }

    const getTipoIp = (IP) => {
        let tipo = '';
        if(IP >= 1 && IP <= 127){
            tipo = 'A';
            bitsHost = 24;
        }
        else if(IP >= 128 && IP <=191){
            tipo = 'B';
            bitsHost = 16;
        }
        else if(IP >= 192 && IP <=223){
            tipo = 'C'
            bitsHost = 8
        }
        return tipo;
    }
    function getMascaraDeRed(IP){
        let mascara = '';
        if(IP >= 1 && IP <= 127) mascara = '255.0.0.0';
        else if(IP >= 128 && IP <=191) mascara = '255.255.0.0';
        else if(IP >= 192 && IP <=223) mascara = '255.255.255.0';
        return(mascara);
    }
    function clasificaIP(ip){
        let nuevaIP = ip.split('.');
        setTipo(getTipoIp(nuevaIP[0]));
        setMascaraRed(getMascaraDeRed(nuevaIP[0]));
    }
    const handleSubmit = (e) => {
        e.preventDefault();
        clasificaIP(IP)
        
    }

    return (
        <div className="flex flex-col justify-around gap-10">
           <div className="flex justify-around gap-10">
            <form 
                    onSubmit={handleSubmit}
                    className="flex gap-2 items-center"
                >
                    <label htmlFor="ip">Dirección ip:</label>
                    <input 
                        className="border shadow-lg p-3 rounded-lg"
                        value={IP} 
                        onChange={handleChange}
     
                        type="text" 
                        placeholder="192.168.124.0" 
                        id="ip" 
                        name="ip"/>
                    <button className="text-white bg-blue-600 p-3 w-28 rounded-md">Enviar</button>
                </form>
                <div className="p-2 bg-white shadow-lg">
                    <h2>Clase: {Tipo}</h2>
                    <h2>Mascara de red: {MascaraRed} </h2>
                </div>
           </div>
            <div className="flex gap-10 items-center">
                <select 
                    value={TipoSubNet} 
                    className="bg-white shadow-lg p-3 rounded-md"
                    onChange={(e) => setTipoSubNet(e.target.value)}
                >    
                    <option>Host</option>
                    <option>Subred</option>
                    <option>Prefijo</option>
                </select>
                <div>
                    <input
                        onChange={(e) => setnTipoS(e.target.value)}
                        value={nTipoS}
                        className=" p-3 border rounded-md shadow-lg" type="number" id="nTipoS" name="nTipoS"/>
                </div>
                <div className="p-2 bg-white shadow-lg">
                    <h2>Subredes:</h2>
                    <h2>Host:</h2>
                    <h2>Mascara de subred: </h2>
                </div>
            </div>
        </div>
    )
}

export default InputIP
