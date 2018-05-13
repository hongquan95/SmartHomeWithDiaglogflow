// blynkRes.js
// ========
const axios = require("axios");
module.exports = {
  get_pin_value: async function (url) {
    try {
      let json = await axios.get(url);
      return json;
    }
    catch(e) {
      console.log("Error =",e);
      return {error: "An unknown error"};
    }
  },
  write_pin_value_via_get:  async function (url) {
    try{
      let json = axios.get(url);
      return json;
    }
    catch(e) {
      console.log("Error =",e);
      return {error: "An unknown error"};
    }

  },
  write_pin_value_via_put:  async function (url, value) {
    try {
      let json = axios.put(url, { body: value}) //"[\"1\"]"
      return json;
    }
    catch(e) {
      console.log("Error =",e);
      return {error: "An unknown error"};
    }
  },
};
