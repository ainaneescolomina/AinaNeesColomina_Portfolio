const input = document.getElementById("input");
const output = document.getElementById("output");

function print(text) {
    text.split("\n").forEach(line => {
        output.innerHTML += `<div>${line}</div>`;
    });

    output.scrollTop = output.scrollHeight;
}

function formatLine(line) {
    return line.replace(
        /(https?:\/\/[^\s]+)/g,
        url => `<a href="${url}" target="_blank">${url}</a>`
    );
}

function handleCommand(cmd) {
    const result = Module.ccall(
        "process_command",
        "string",
        ["string"],
        [cmd]
    );

    handleOutput(result);
}

function handleOutput(text) {
    // 1. detect window trigger
    const windowMatch = text.match(/\[OPEN_WINDOW:(.+?)\]/);

    if (windowMatch) {
        const projectName = windowMatch[1];
        openProjectWindow(projectName);
    }

    // 2. still print everything in logs (cleaned)
    const cleaned = text.replace(/\[OPEN_WINDOW:.*?\]/, "");
    print(cleaned);
}

function openProjectWindow(name) {
    const win = document.createElement("div");
    win.className = "project-window";

    win.innerHTML = `
        <div class="window-header">${name}</div>
        <img src="assets/${name}.png" />
    `;

    document.body.appendChild(win);
}

input.addEventListener("keydown", function (e) {
    if (e.key === "Enter") {
        const cmd = input.value.trim();

        print("> " + cmd);
        handleCommand(cmd);

        input.value = "";
    }
});