tempC_container = document.getElementById("tempC-container");
tempF_container = document.getElementById("tempF-container");
humidity_Container = document.getElementById("humidity-container");
async function fetchData() {
  try {
    const response = await fetch("http://192.168.2.29/data");
    const data = await response.json();
    document.getElementById("tempC").innerText = data.temperature + " °C";
    document.getElementById("tempF").innerText = data.temperatureF + " °F";
    document.getElementById("humidity").innerText = data.humidity + " %";
   const humidityValue = parseFloat(data.humidity); // Already a number from JSON, but safer to confirm
    if (humidityValue > 80) {
  humidity_Container.classList.add("red-glow");
  } else {
  humidity_Container.classList.remove("red-glow");
  }

  } catch (error) {
    console.error("Error fetching data:", error);
  }
}


setInterval(fetchData, 2000); // Fetch data every 2 seconds



