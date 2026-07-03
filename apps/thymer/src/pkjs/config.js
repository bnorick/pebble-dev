module.exports = function buildConfig(settings) {
  settings = settings || {};

  return [
    {
      type: "heading",
      defaultValue: "Thymer Settings"
    },
    {
      type: "text",
      defaultValue: 'Configure Thymer appearance and timer definitions. <a href="https://bnorick.github.io/pebble-dev/thymer/guide/getting-started" target="_blank" rel="noopener noreferrer">Open the config documentation</a>.'
    },
    {
      type: "section",
      items: [
        {
          type: "heading",
          defaultValue: "Appearance"
        },
        {
          type: "toggle",
          messageKey: "IconsEnabled",
          label: "Icons enabled",
          description: "Show the watch-side button icons and related hints.",
          defaultValue: settings.iconsEnabled !== false
        },
        {
          type: "toggle",
          messageKey: "BackgroundEnabled",
          label: "Background enabled",
          description: "Show the full-screen background image on supported watches.",
          defaultValue: settings.backgroundEnabled !== false
        },
        {
          type: "toggle",
          messageKey: "TimerAccentEnabled",
          label: "Timer accent enabled",
          description: "Show the timer focus panel image behind the active countdown.",
          defaultValue: settings.timerAccentEnabled !== false
        }
      ]
    },
    {
      type: "section",
      items: [
        {
          type: "heading",
          defaultValue: "Config"
        },
        {
          type: "textarea",
          messageKey: "TomlConfig",
          label: "TOML configuration",
          description: "Paste Thymer timer config here.",
          defaultValue: settings.toml || "",
          attributes: {
            placeholder: "# Paste Thymer config here",
            rows: 18
          }
        }
      ]
    },
    {
      type: "submit",
      defaultValue: "Save"
    }
  ];
};
