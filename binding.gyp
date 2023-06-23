{
    "targets": [
        {
            "target_name": "gpiod",
            "sources": ["src/libgpiod.cc"],
            "include_dirs": [
                "<!(node -e \"require('node-api-headers')\")/include",
                "<!(node -e \"require('nan')\")",
            ],
            "conditions": [
                [
                    'OS=="mac"',
                    {
                        "variables": {
                            "libgpiod": "<!(which libgpiod >/dev/null && echo true || echo false)"
                        },
                        "conditions": [
                            [
                                'libgpiod == "true"',
                                {"link_settings": {"libraries": ["-lgpiod"]}},
                            ],
                        ],
                    },
                ]
            ],
        }
    ]
}
