{
  "targets": [
    {
      "target_name": "gpiod",
      "sources": [
        "src/libgpiod.cc"
      ],
      "include_dirs": [
        "<!(node -e \"require('node-api-headers')\")/include",
        "<!(node -e \"require('nan')\")"
      ],
      "link_settings": {
        "libraries": [
          "-lgpiod"
        ]
      }
    }
  ]
}