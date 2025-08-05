import React from "react";

export default function KarelIcon({
    className
}) {
    return (
                  <img
            src="/img/karel.png"
            alt="Karel Robot"
            className={className}
            onError={(e) => {
              console.warn('Karel icon not found at /img/karel.png');
              e.target.style.display = 'none';
            }}
            />
    )
}
