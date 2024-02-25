local function merge()
  io.popen("merger/cmake-build-release/merger 2>/dev/null", "r")
end

vim.api.nvim_create_autocmd("BufWritePost", {
  pattern = { "main.cpp" },
  callback = merge
})


require("auto-save").setup(
  {
    callbacks = {
      after_saving = merge,
    },

    debounce_delay = 500000,
    debug = true
  }
)


