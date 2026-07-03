import { defineConfig } from "vitepress";

export default defineConfig({
  title: "Thymer",
  description: "Timer configuration reference for the Thymer Pebble app.",
  base: "/pebble-dev/thymer/",
  head: [
    ["link", { rel: "icon", type: "image/png", href: "/pebble-dev/thymer/favicon.png" }],
  ],
  cleanUrls: true,
  lang: "en-US",
  lastUpdated: false,
  markdown: {
    theme: {
      light: "solarized-light",
      dark: "solarized-light",
    },
  },
  themeConfig: {
    siteTitle: false,
    logo: {
      src: "/logo-thymer.png",
      alt: "Thymer",
    },
    logoLink: "/guide/getting-started",
    nav: [
      { text: "Guide", link: "/guide/getting-started" },
      { text: "Reference", link: "/reference/config-format" },
      { text: "Cookbook", link: "/cookbook/concepts" },
    ],
    search: {
      provider: "local",
    },
    socialLinks: [
      { icon: "github", link: "https://github.com/bnorick/pebble-dev/tree/main/apps/thymer" },
    ],
    footer: {
      message: "Timer configuration docs for Thymer.",
      copyright: "Pebble app docs for the pebble-dev repository",
    },
    sidebar: [
      {
        text: "Guide",
        items: [
          { text: "Getting Started", link: "/guide/getting-started" },
        ],
      },
      {
        text: "Reference",
        items: [
          { text: "Config Format", link: "/reference/config-format" },
          { text: "Timers", link: "/reference/timers" },
          { text: "Patterns and Time", link: "/reference/patterns-and-time" },
          { text: "Vibration", link: "/reference/vibration" },
          { text: "Triggers", link: "/reference/triggers" },
        ],
      },
      {
        text: "Cookbook",
        items: [
          { text: "General Concepts", link: "/cookbook/concepts" },
          { text: "Breathing", link: "/cookbook/breathing" },
          { text: "Exercise", link: "/cookbook/exercise" },
          { text: "Kids", link: "/cookbook/kids" },
          { text: "Full Config", link: "/cookbook/full-config" },
        ],
      },
      {
        text: "Troubleshooting",
        items: [
          { text: "Common Errors", link: "/troubleshooting/common-errors" },
        ],
      },
    ],
    outline: {
      level: [2, 3],
    },
  },
});
