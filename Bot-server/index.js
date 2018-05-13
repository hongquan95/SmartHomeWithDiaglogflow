"use strict";
var blynk = require('./blynkRes');
const express = require("express");
const bodyParser = require("body-parser");
// const axios = require("axios");
// Quan:     3dddac1594e74646bde292060be39113
//Tu:     dd6aa1dccaec458d9b8a29f0e8168339
//Token Quan-tapit:  eac41632ae5c4a8eba8bdc2cfb1def5c
const restService = express();
restService.set('view engine', 'ejs');
var googleReq, blynkRes;

restService.use(
  bodyParser.urlencoded({
    extended: true
  })
);

//-------------Enum declare-----------------------

var state = {on: "0", off: "1", open: "0", close: "1"};
var room = {bed:"bedroom",kitchen:"kitchen", living: "living", bath: "bath"};
var sensor = {temp: "temperature", humi: "humidity", gas: "gas"};
var device = {led: "led", fan: "fan", door: "door", heater: "heater", air_conditioner: "air_conditioner"};
var deviceNum = {fan: "0", heater: "1", air_conditioner: "2"};

// var pin = {bedroom: "D14", kitchen: "D12",door: "D13", fan: "D0", heater: "D2",
//            temperature: "V1", humidity: "V0", gas: "D5", all_device: "V10", check_all: "V11", 
//            recieve_stt: "V12", pass_word: "V13", timer: "V23", timerStart: "V24", timerEnd: "V25" }; 
var pin = {living: "V1", bedroom: "V2",  fan: "V3", heater: "V4", kitchen: "V5", bath: "V6",  door: "V7", air_conditioner: "V8", window: "V9",
           temperature: "V30", humidity: "V31", gas: "V32", all_device: "V19", check_all: "V11", 
           recieve_stt: "V12", pass_word: "V13", timer: "V23", timerStart: "V24", timerEnd: "V25" };
          
// var blynk_url = 'http://188.166.206.43/eac41632ae5c4a8eba8bdc2cfb1def5c/'
var blynk_url = 'http://61.14.232.216:8088/eac41632ae5c4a8eba8bdc2cfb1def5c/';
var res = {get: "get/", update: "update/"};

//-------------------------------------------------

//------Return json to respon ----------------

function getReturn(g_res, speech){
  g_res.json({
    speech: speech,
    displayText: speech,
    source: "webhook-echo-sample"
    });
    console.log("GJson = ",speech);
    console.log("TYPE = ",typeof(speech));
}

//-----------------Process Json----------------------------

function processJson(raw)
{
  var a = {};
  a.action = raw.action
  if (raw.action.includes("o."))
    a.parameters = raw.parameters;
  else
    raw.contexts.forEach(ele => {
      if ( raw.action == ele.name )
      a.parameters = ele.parameters;
    });
  return a;
}

//----------------------------------------------------------

restService.use(bodyParser.json());

//----------------Read or Write value pin --------------------------

restService.post("/echo", function(g_req, g_res) {
  googleReq = g_req.body.result;
  var para = processJson(googleReq);
  console.log("PARA =",para);

    switch (para.action)
    {
      case 'turn-it-on-off-with-led':
      case 'ask-led-room-state' :
      case 'o.control-led' :
      
        if ( para.parameters.led && para.parameters.state && para.parameters.room == "" )
          return getReturn(g_res,"An unknown error");
        else
        {
          // http://blynk-cloud.com/4ae3851817194e2596cf1b7103603ef8/update/D8?value=1
          let url = blynk_url + res.update + pin[para.parameters.room] + '?value=' + state[para.parameters.state];
          console.log("URL = ", url);
          blynk.write_pin_value_via_get(url).then( function(b_res) {
            if (b_res.error != undefined) return getReturn(g_res,b_res.error);
            else {
              blynkRes = b_res.body;
              var speech = "The led in " + para.parameters.room + " is " + para.parameters.state;
              return getReturn(g_res,speech);    
            }
          });
          // getReturn(g_res,url);
        }
        break;
      
      case 'turn-it-on-off' :
      case 'o.control-a-device' :
      case 'ask-device-state' :

        if ( para.parameters.device && para.parameters.state == "" )
          return getReturn(g_res,"An unknown error");
        else
        {
          // http://blynk-cloud.com/4ae3851817194e2596cf1b7103603ef8/update/D8?value=1
          let url = blynk_url + res.update + pin[para.parameters.device] + '?value=' + state[para.parameters.state]
          console.log("URL = ", url);
          blynk.write_pin_value_via_get(url).then( function(b_res) {
            if (b_res.error != undefined) return getReturn(g_res,b_res.error);
            else {
              blynkRes = b_res.body;
              var speech = "The " + para.parameters.device + " is " + para.parameters.state;
              return getReturn(g_res,speech);    
            }
          });
          // getReturn(g_res,url);
        }
        break;

      case 'o.open-close-door' :
        
        if ( para.parameters.device == "" )
          return getReturn(g_res,"An unknown error");
        else
        {
          // http://blynk-cloud.com/4ae3851817194e2596cf1b7103603ef8/update/D8?value=1
          let url = blynk_url + res.update + pin[para.parameters.door] + '?value=' + state.close;
          console.log("URL = ", url);
          blynk.write_pin_value_via_get(url).then( function(b_res) {
            if (b_res.error != undefined) return getReturn(g_res,b_res.error);
            else {
              blynkRes = b_res.body;
              var speech = "The door is closed ";
              return getReturn(g_res,speech);    
            }
          });
          // getReturn(g_res,url);
        }
        break;

      case 'o.open-close-window' :
  
        if ( para.parameters.window == "" )
          return getReturn(g_res,"An unknown error");
        else
        {
          // http://blynk-cloud.com/4ae3851817194e2596cf1b7103603ef8/update/D8?value=1
          let url = blynk_url + res.update + pin[para.parameters.window] + '?value=' + state[para.parameters.make];
          console.log("URL = ", url);
          blynk.write_pin_value_via_get(url).then( function(b_res) {
            if (b_res.error != undefined) return getReturn(g_res,b_res.error);
            else {
              blynkRes = b_res.body;
              var speech = "The window is ";
              speech += para.parameters.make == "open" ? "opened" : "closed" ;
              return getReturn(g_res,speech);    
            }
          });
          // getReturn(g_res,url);
        }
        break;

      

      case 'o.make-all' :
        
        if ( para.parameters.state == "" )
          return getReturn(g_res,"An unknown error");
        else
        {
          // http://blynk-cloud.com/4ae3851817194e2596cf1b7103603ef8/update/D8?value=1
          let url = blynk_url + res.update + pin.all_device + '?value=' + state[para.parameters.state]
          console.log("URL = ", url);
          blynk.write_pin_value_via_get(url).then( function(b_res) {
            if (b_res.error != undefined) return getReturn(g_res,b_res.error);
            else {
              blynkRes = b_res.body;
              var speech = "All devices are turn " + para.parameters.state;
              return getReturn(g_res,speech);    
            }
          });
        }
        break;

      case 'ask-status-led-room' :
      case 'o.check-status-led' :
      
        if ( para.parameters.room && para.parameters.led == "" )
          return getReturn(g_res,"An unknown error");
        else
        {
          //  http://blynk-cloud.com/dd6aa1dccaec458d9b8a29f0e8168339/get/V10
          let url = blynk_url + res.get + pin[para.parameters.room];
          console.log("URL = ", url);
          blynk.get_pin_value(url).then( function(b_res) {
            if (b_res.error != undefined) return getReturn(g_res,b_res.error);
            else {
              blynkRes = b_res.data;
              var speech = "The led in " + para.parameters.room + " is ";
              speech += b_res.data == '0' ? "on" : "off";
              return getReturn(g_res,speech);    
            }
          });
        }
        break;
      case 'o.check-door':  
        if ( para.parameters.door == "" ) return getReturn(g_res,"An unknown error");
      case 'o.check-window':  
        if ( para.parameters.window == "" ) return getReturn(g_res,"An unknown error");
      case 'o.check-device' :
        if ( para.parameters.device == "" )
          return getReturn(g_res,"An unknown error");
        else
        {
          //  http://blynk-cloud.com/dd6aa1dccaec458d9b8a29f0e8168339/get/V10
          let url = blynk_url + res.get;
          if (para.action == 'o.check-door') 
            url += pin[para.parameters.door];
          else if (para.action == 'o.check-device') 
            url += pin[para.parameters.device];
          else 
            url += pin[para.parameters.window];

          console.log("URL = ", url);
          blynk.get_pin_value(url).then( function(b_res) {
            if (b_res.error != undefined) return getReturn(g_res,b_res.error);
            else {
              blynkRes = b_res.data;
              var speech = "The  ";
              if ( para.action == 'o.check-door' )
              {
                speech += para.parameters.door + " is ";
                speech += b_res.data == '0' ? "opened" : "closed"; 
              }
              else if ( para.action == 'o.check-device' )
              {
                speech +=  para.parameters.device + " is ";
                speech += b_res.data == '0' ? "on" : "off";
              }
              else 
              {
                speech +=  para.parameters.window + " is ";
                speech += b_res.data == '0' ? "opend" : "closed";
              }
              return getReturn(g_res,speech);    
            }
          });
        }
        break;
        
      case 'o.check-all' :
        {
          //  http://blynk-cloud.com/dd6aa1dccaec458d9b8a29f0e8168339/get/V10
          let url = blynk_url + res.update + pin.check_all + '?value=0';
          console.log("URL = ", url);
          let url2 = blynk_url + res.get + pin.recieve_stt;
          console.log("URL2 = ", url2);
          blynk.write_pin_value_via_get(url).then( function(b_res) {
            if (b_res.error != undefined) return getReturn(g_res,b_res.error);
            else {
            blynk.get_pin_value(url2).then( function(b_res2) {
              if (b_res2.error != undefined) return getReturn(g_res,b_res2.error);
              else {
                blynkRes = b_res2.data;
                blynkRes = JSON.stringify(blynkRes);
                blynkRes = blynkRes.replace('["{','');
                blynkRes = blynkRes.replace('}"]','');
                console.log("STT = ",blynkRes);
                var speech = JSON.stringify(blynkRes);
                return getReturn(g_res,speech);    
                }
              });
            }
          });
        }
        break;

      case 'o.see-sensor' :

        
        if ( para.parameters.sensor == "" )
          return getReturn(g_res,"An unknown error");
        else
        {
          //  http://blynk-cloud.com/dd6aa1dccaec458d9b8a29f0e8168339/get/V10
          let url = blynk_url + res.get + pin[para.parameters.sensor];
          console.log("URL = ", url);
          blynk.get_pin_value(url).then( function(b_res) {
            if (b_res.error != undefined) return getReturn(g_res,b_res.error);
            else
            {
              blynkRes = b_res.data;
              var speech = "The " + para.parameters.sensor + " is " + blynkRes;
              return getReturn(g_res,speech);    
            }
          });
        }
        break;

      
      case 'o.check-password':
      
        if ( para.parameters.password == "" )
          return getReturn(g_res,"An unknown error");
        else
        {
          //  http://blynk-cloud.com/dd6aa1dccaec458d9b8a29f0e8168339/get/V10
          let url = blynk_url + res.get + pin.pass_word;
          console.log("URL = ", url);
          blynk.get_pin_value(url).then( function(b_res) {
            if (b_res.error != undefined) return getReturn(g_res,b_res.error);
            else
            {
              blynkRes = b_res.data;
              console.log("RESPASS=",blynkRes);

              if ( blynkRes == para.parameters.password )
              {
                let url2 = blynk_url + res.update + pin.door + '?value=' + state.open;
                console.log("URL2 = ", url2);
                blynk.write_pin_value_via_get(url2).then( function(b_res) {
                  if (b_res.error != undefined) return getReturn(g_res,b_res.error);
                  else {
                    var speech = "The door is opend";
                    return getReturn(g_res,speech);    
                  }
                });
              }
              else
              {
                var speech = "Wrong password, Retype!!!";
                return getReturn(g_res,speech);    
              }
            
            }
          });
        }
        break;

      case 'o.confirm-pass':
        if (  para.parameters.newpass < 1000  )
          return getReturn(g_res,"The password is too short");
        else
        {
          // http://blynk-cloud.com/4ae3851817194e2596cf1b7103603ef8/update/D8?value=1
          let url = blynk_url + res.update + pin.pass_word + '?value=' + para.parameters.newpass;
          console.log("URL = ", url);
          blynk.write_pin_value_via_get(url).then( function(b_res) {
            if (b_res.error != undefined) return getReturn(g_res,b_res.error);
            else {
              blynkRes = b_res.body;
              var speech = "The password is changed";
              return getReturn(g_res,speech);    
            }
          });
        }
        break;

 

      case 'o.start-timer' :
        if (  para.parameters.time &&  para.parameters.device == "" )
          return getReturn(g_res,"Unknow error");
        else
        {
          let timeStr = JSON.stringify(para.parameters.time)  ;   
          let hh = timeStr.slice(1,3);
          let mm = timeStr.slice(4,6);
          let url = blynk_url + res.update + pin.timerStart + '?value='+ hh + ":"+ mm + ":" + deviceNum[para.parameters.device];
          console.log("TIME TIME TIME START = ", url);
        blynk.write_pin_value_via_get(url).then( function(b_res) {
          if (b_res.error != undefined) return getReturn(g_res,b_res.error);
          else {
            blynkRes = b_res.data;
            var speech = "Start Timer is set";
            return getReturn(g_res,speech);    
            }
          });
        }
      break;
      case 'o.end-timer' :
        if (  para.parameters.time == "" )
          return getReturn(g_res,"Unknow error");
        else
        {
          let timeStr = JSON.stringify(para.parameters.time)  ;   
          let hh = timeStr.slice(1,3);
          let mm = timeStr.slice(4,6);
          let url = blynk_url + res.update + pin.timerEnd + '?value='+ hh + ":"+ mm + ":" + deviceNum[para.parameters.device];
          console.log("TIME END = ", url);
          blynk.write_pin_value_via_get(url).then( function(b_res) {
          if (b_res.error != undefined) return getReturn(g_res,b_res.error);
          else {
            blynkRes = b_res.data;
            var speech = "End Timer is set";
            return getReturn(g_res,speech);    
            }
          });
        }
      break;
      
      default:
      getReturn(g_res,'Invalid');
    }
});

//-----------------------------------------------------------------------

restService.get('/echo', function (req, res) {
  res.locals.google = googleReq ;
  res.locals.blynk = blynkRes;
  res.render('pages/echo');
})

restService.listen(process.env.PORT || 8000, function() {
  console.log("Server up and listening");
});
