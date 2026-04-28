const input = document.getElementById("input");
const output = document.getElementById("output");

function print(text) {
  output.innerHTML += `<div>${text}</div>`;
}

function handleCommand(cmd) {
  const result = Module.ccall(
    "process_command",   // C++ function name
    "string",            // return type
    ["string"],          // input type
    [cmd]                // arguments
  );

  print(result);
}

input.addEventListener("keydown", function (e) {
  if (e.key === "Enter") {
    const cmd = input.value.trim();

    print(`> ${cmd}`);
    handleCommand(cmd);

    input.value = "";
  }
});