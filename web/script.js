const input = document.getElementById("input");
const output = document.getElementById("output");

function print(text) {
    output.innerHTML += `<div>${text}</div>`;
    output.scrollTop = output.scrollHeight;
}

function handleCommand(cmd) {
    const result = Module.ccall(
        "process_command",
        "string",
        ["string"],
        [cmd]
    );

    print(result);
}

input.addEventListener("keydown", function (e) {
    if (e.key === "Enter") {
        const cmd = input.value.trim();

        print("> " + cmd);
        handleCommand(cmd);

        input.value = "";
    }
});