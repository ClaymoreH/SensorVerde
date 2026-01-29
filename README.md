# 🌱 SensorVerde - Sistema IoT de Monitoramento Ambiental

<div align="center">

![Status](https://img.shields.io/badge/status-active-success.svg)
![Node-RED](https://img.shields.io/badge/Node--RED-8F0000?logo=nodered&logoColor=white)
![MQTT](https://img.shields.io/badge/MQTT-660066?logo=mqtt&logoColor=white)
![Firebase](https://img.shields.io/badge/Firebase-FFCA28?logo=firebase&logoColor=black)

Sistema completo de monitoramento ambiental com ESP32, sensores IoT e visualização em tempo real.

</div>

---

## Sobre o Projeto

O **SensorVerde** é um sistema IoT que coleta dados ambientais através de dispositivos ESP32 equipados com sensores, transmite via protocolo MQTT e exibe as informações em dashboards interativos usando Node-RED.

### Sensores Monitorados
- 🌡️ **Temperatura** - Medição em °C
- 🌿 **Umidade do Solo** - Nível de hidratação do solo

### Arquitetura

```
ESP32 + Sensores  →  MQTT Broker  →  Node-RED  →  Firestore
                                        ↓
                                   Dashboard Web
```

---

## Características

-  **Tempo Real** - Visualização instantânea dos dados dos sensores
-  **Gráficos Históricos** - Análise temporal de temperatura e umidade
-  **Sistema de Alertas** - Notificações quando valores ultrapassam limites
-  **Armazenamento Cloud** - Backup automático no Firebase Firestore
-  **Dashboard Responsivo** - Interface adaptável para diferentes dispositivos
-  **Multi-dispositivo** - Suporte para múltiplos ESP32 simultaneamente

---

##  Instalação

### Instalação no Linux

4. **Atualizar Sistema**
```bash
sudo apt update && sudo apt upgrade -y
```

4. **Instalar Node.js e NPM**
```bash
curl -fsSL https://deb.nodesource.com/setup_18.x | sudo -E bash -
sudo apt install -y nodejs
```
4. **Instalar Node-RED**
```bash
sudo npm install -g --unsafe-perm node-red
```

4. **Instalar Depedências**
```bash
npm install node-red-contrib-cloud-firestore
npm install @flowfuse/node-red-dashboard
```
4. **Clonar Projeto**
```bash
git clone https://github.com/seu-usuario/sensorverde.git
cd sensorverde
```

4. **Executar**
```bash
node-red
```

Acesse: `http://localhost:1880`

---

### Instalação no Windows

#### Método 1: Via Instalador (Recomendado)

1. **Baixar Node.js**
   - Acesse: https://nodejs.org/
   - Baixe a versão LTS
   - Execute o instalador e siga as instruções

2. **Instalar Node-RED**
   ```cmd
   # Abra o PowerShell como Administrador
   npm install -g --unsafe-perm node-red
   ```

3. **Instalar Dependências**
   ```cmd
   npm install node-red-contrib-cloud-firestore
   npm install @flowfuse/node-red-dashboard
   ```

4. **Clonar Projeto**
   ```cmd
   git clone https://github.com/seu-usuario/sensorverde.git
   cd sensorverde
   ```

5. **Executar**
   ```cmd
   node-red
   ```
---

## Configuração

### 1. Firebase Setup

1. Acesse [Firebase Console](https://console.firebase.google.com/)
2. Crie um novo projeto
3. Ative o **Firestore Database**
4. Gere uma chave de serviço:
   - Project Settings → Service Accounts
   - Generate New Private Key
5. Baixe o arquivo JSON e salve como `firebase-credentials.json`

### 2. Importar Flows no Node-RED

1. Abra o Node-RED em `http://localhost:1880`
2. Menu (≡) → Import 
3. Abra o arquivo `SensorVerde_Flows.json`
4. Clique em "Import"

### 3. Configurar Firebase no Node-RED

1. Clique duas vezes no nó **"Firestore In"** ou **"Firestore Out"**
2. Edite a configuração do **Firebase Admin**
3. Cole o conteúdo do `firebase-credentials.json`

---

## Uso

### Acessar Dashboard

Após iniciar o Node-RED, acesse:

```
http://localhost:1880/dashboard
```

### Programar ESP32

1. Abra a pasta `wokwi/` do projeto
2. Configure o tópico MQTT: `sensorVerde/<numero_do_esp>`
3. Ajuste os pinos dos sensores no código
4. Ajuste a API do weatherapi
4. Faça upload para o ESP32

---


<div align="center">

**[⬆ Voltar ao topo](#-sensorverde---sistema-iot-de-monitoramento-ambiental)**

</div>
